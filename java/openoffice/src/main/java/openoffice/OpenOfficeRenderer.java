package openoffice;

import java.io.File;

import com.sun.star.beans.PropertyValue;
import com.sun.star.frame.XComponentLoader;
import com.sun.star.frame.XDesktop;
import com.sun.star.frame.XModel;
import com.sun.star.lang.EventObject;
import com.sun.star.lang.XComponent;
import com.sun.star.lang.XMultiComponentFactory;
import com.sun.star.uno.UnoRuntime;
import com.sun.star.uno.XComponentContext;
import com.sun.star.util.XCloseable;
import com.sun.star.view.PrintJobEvent;
import com.sun.star.view.PrintableState;
import com.sun.star.view.XPrintJobBroadcaster;
import com.sun.star.view.XPrintJobListener;
import com.sun.star.view.XPrintable;

public class OpenOfficeRenderer {

    public static void setInstallPath(String installPath) {
        OpenOfficeProcess.setInstallPath(installPath);
    }

    public void render(String inputPath, String outputPath, String printerDriver)
            throws Exception {
        OpenOfficeProcess process = new OpenOfficeProcess();
        try {
            // 1. Connected to a running office ...
            XComponentContext xContext = process.bootstrap(); // get the remote office component context
            XMultiComponentFactory xMCF = xContext.getServiceManager(); // get the remote office service manager
            Object oDesktop = xMCF.createInstanceWithContext("com.sun.star.frame.Desktop", xContext); // Get the root frame (i.e. desktop) of Open Office framework.
            XComponentLoader xCompLoader = (XComponentLoader) UnoRuntime.queryInterface(XComponentLoader.class, oDesktop); // Desktop has 3 interfaces. The XComponentLoader interface provides ability to load components.

            // 2. Open document ...
            File sourceFile = new File(inputPath);
            StringBuffer sUrl = new StringBuffer("file:///");
            sUrl.append(sourceFile.getCanonicalPath().replace('\\', '/'));
            XComponent xComp = xCompLoader.loadComponentFromURL(sUrl.toString(), "_blank", 0, new PropertyValue[0]); // Load a document, which will be automaticly displayed

            // 3. Connect XPrintable
            XPrintable xPrintable = (XPrintable) UnoRuntime.queryInterface(XPrintable.class, xComp); // Querying for the interface XPrintable on the loaded document

            // 4. Set printer
            PropertyValue printerProp[] = new PropertyValue[1]; // Setting the property "Name" for the favoured printer (name of IP address)
            printerProp[0] = new PropertyValue();
            printerProp[0].Name = "Name";
            printerProp[0].Value = printerDriver;
            xPrintable.setPrinter(printerProp); // Setting the name of the printer

            // 5. Set listener
            XPrintJobBroadcaster broadcaster = UnoRuntime.queryInterface(XPrintJobBroadcaster.class, xPrintable);
            SyncXPrintJobListener listener = new SyncXPrintJobListener();
            broadcaster.addPrintJobListener(listener);

            // 6. Set file
            PropertyValue printProp[] = new PropertyValue[2];
            printProp[0] = new PropertyValue();
            printProp[0].Name = "FileName";
            printProp[0].Value = outputPath;

            // 7. Rendering
            xPrintable.print(printProp); // Printing the loaded document

            // 8. Wait for spool to complete
            try {
                waitForSpoolToComplete(listener, 60000, 500);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            } finally {
                closeComponent(xComp);
                closeDesktop(oDesktop);
            }
        } finally {
            process.destroy();
        }
    }

    private void waitForSpoolToComplete(SyncXPrintJobListener listener,
            long timeout, long pollingInterval)
            throws RenderingFailedException, InterruptedException {
        int maxCount = (int) (timeout / pollingInterval);
        for (int i = 0; i < maxCount; i++) {
            PrintableState state = listener.getState();
            if (state == null || state == PrintableState.JOB_STARTED
                    || state == PrintableState.JOB_COMPLETED) {
                Thread.sleep(pollingInterval);
                continue;
            } else if (state == PrintableState.JOB_SPOOLED) {
                return;
            } else if (state == PrintableState.JOB_ABORTED) {
                throw new RenderingFailedException("JOB_ABORTED");
            } else if (state == PrintableState.JOB_FAILED) {
                throw new RenderingFailedException("JOB_FAILED");
            } else if (state == PrintableState.JOB_SPOOLING_FAILED) {
                throw new RenderingFailedException("JOB_SPOOLING_FAILED");
            } else {
                throw new AssertionError("Unknown state: " + state);
            }
        }
        throw new RenderingFailedException("Spool has timed out (timeout = " + timeout + "[ms])");
    }

    private void closeComponent(XComponent xComp) throws Exception {
        XModel xModel = (XModel) UnoRuntime.queryInterface(XModel.class, xComp);
        if (xModel == null)
            return;

        XCloseable xCloseable = (XCloseable) UnoRuntime.queryInterface(XCloseable.class, xModel);
        if (xCloseable != null) {
            xCloseable.close(true);
        } else {
            XComponent xComponent = (XComponent) UnoRuntime.queryInterface(XComponent.class, xModel);
            xComponent.dispose();
        }
    }

    private boolean closeDesktop(Object oDesktop) throws Exception {
        XDesktop xDesktop = (XDesktop) UnoRuntime.queryInterface(XDesktop.class, oDesktop);
        return xDesktop.terminate();
    }

    private class SyncXPrintJobListener implements XPrintJobListener {

        private PrintableState state;

        @Override
        public void printJobEvent(PrintJobEvent event) {
            state = event.State;
        }

        @Override
        public void disposing(EventObject eventobject) {
        }

        public PrintableState getState() {
            return state;
        }

    }

}
