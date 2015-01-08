import java.util.ArrayList;
import java.util.List;

import javax.print.PrintService;
import javax.print.PrintServiceLookup;

import openoffice.OpenOfficeRenderer;

public class OpenOfficeRendererSample {

    private static final String RESOURCE_DIRECTORY = "src/main/resources/";

    public static void main(String args[]) throws Exception {
        List<String> files = new ArrayList<String>();
        files.add("doc/test.doc");
        files.add("doc/test.xls");
        files.add("doc/test.ppt");

        OpenOfficeRenderer.setInstallPath("C:\\Program Files (x86)\\OpenOffice 4");
        OpenOfficeRenderer renderer = new OpenOfficeRenderer();

        for (String file : files) {
            String filePath = RESOURCE_DIRECTORY + file;
            System.out.println(filePath);
            renderer.render(filePath, filePath + ".prn", getDefaultPrinterDriver());
        }
    }

    private static String getDefaultPrinterDriver() {
        PrintService printService = PrintServiceLookup.lookupDefaultPrintService();
        return printService.getName();
    }

}
