package openoffice;

import java.io.File;
import java.io.IOException;
import java.net.ServerSocket;

import com.sun.star.bridge.UnoUrlResolver;
import com.sun.star.bridge.XUnoUrlResolver;
import com.sun.star.comp.helper.Bootstrap;
import com.sun.star.uno.UnoRuntime;
import com.sun.star.uno.XComponentContext;

public class OpenOfficeProcess {

    private static final String SOFFICE_BIN = "program/soffice.bin";
    private static final String HOST = "localhost";
    private static final int MIN_PORT = 50000;
    private static final int MAX_PORT = 51000;

    private static String sofficePath;
    private Process ooServer;

    public static void setInstallPath(String installPath) {
        sofficePath = installPath + File.separator + SOFFICE_BIN;
    }

    public XComponentContext bootstrap() throws IOException {
        int port = getLocalPort();
        ooServer = runOoServer(HOST, port);
        return connectToOoServer(HOST, port);
    }

    public XComponentContext bootstrap(int localPort) throws IOException {
        tryToRunServer(localPort);
        ooServer = runOoServer(HOST, localPort);
        return connectToOoServer(HOST, localPort);
    }

    public void destroy() {
        if (ooServer != null)
            ooServer.destroy();
    }

    private int getLocalPort() throws IOException {
        for (int port = MIN_PORT; port <= MAX_PORT; port++)
            if (canRunServer(port))
                return port;
        throw new IOException("Could not use " + MIN_PORT + " ~ " + MAX_PORT + " port");
    }

    private Process runOoServer(String host, int port) throws IOException {
        ProcessBuilder builder = new ProcessBuilder();
        builder.redirectErrorStream(true);
        builder.command(sofficePath,
                "-headless",
                "-invisible",
                "-minimized",
                "-nolockcheck",
                "-nologo",
                "-norestore",
                "-nofirststartwizard",
                getAcceptOption(host, port)
                );
        return builder.start();
    }

    private String getAcceptOption(String host, int port) {
        return "-accept=socket,host=" + host + ",port=" + port + ";urp;";
    }

    private XComponentContext connectToOoServer(String host, int port) throws IOException {
        XComponentContext xLocalContext;
        try {
            xLocalContext = Bootstrap.createInitialComponentContext(null);
        } catch (Exception e) {
            throw new IOException(e);
        }
        XUnoUrlResolver xUnoUrlResolver = UnoUrlResolver.create(xLocalContext);
        Object resolvedObject = retryConnectOoToServer(xUnoUrlResolver, getUnoURL(host, port), 5, 100);
        return UnoRuntime.queryInterface(XComponentContext.class, resolvedObject);
    }

    private String getUnoURL(String host, int port) {
        return "uno:socket,host=" + host + ",tcpNoDelay=1,port=" + port + ";urp;StarOffice.ComponentContext";
    }

    private Object retryConnectOoToServer(XUnoUrlResolver xUnoUrlResolver,
            String unoURL, int retryCoutnt, long sleepingTime)
            throws IOException {
        Exception unoException = null;
        for (int i = 0; i < retryCoutnt; i++) {
            try {
                return xUnoUrlResolver.resolve(unoURL);
            } catch (Exception e) {
                unoException = e;
                try {
                    Thread.sleep(sleepingTime);
                } catch (InterruptedException ie) {
                    Thread.currentThread().interrupt();
                }
            }
        }
        throw new IOException(unoException);
    }

    private static boolean canRunServer(int port) throws IOException {
        ServerSocket socket = null;
        try {
            socket = new ServerSocket(port);
            return true;
        } catch (IOException e) {
            return false;
        } finally {
            if (socket != null)
                socket.close();
        }
    }

    private static void tryToRunServer(int port) throws IOException {
        ServerSocket socket = null;
        try {
            socket = new ServerSocket(port);
        } finally {
            if (socket != null)
                socket.close();
        }
    }

}
