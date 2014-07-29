import java.io.File;
import groovy.lang.GroovyShell;

public class GroovyInvoker {

    public static void main(String[] args) throws Exception {
        GroovyShell groovy = new GroovyShell();
        groovy.run(new File("src/main/groovy/hello.groovy"), args);
    }

}
