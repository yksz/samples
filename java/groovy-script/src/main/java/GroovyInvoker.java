import groovy.lang.GroovyShell;

import java.io.File;
import java.io.FileReader;
import java.io.Reader;

import javax.script.Bindings;
import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.SimpleBindings;

public class GroovyInvoker {

    private static void invokeScriptEngine(File file, String[] args) throws Exception {
        ScriptEngineManager manager = new ScriptEngineManager();
        ScriptEngine engine = manager.getEngineByName("groovy");
        Bindings bindings = new SimpleBindings();
        bindings.put("args", args);
        try (Reader reader = new FileReader(file)) {
            engine.eval(reader, bindings);
        }
    }

    private static void invokeGroovyShell(File file, String[] args) throws Exception {
        GroovyShell groovy = new GroovyShell();
        groovy.run(file, args);
    }

    public static void main(String[] args) throws Exception {
        File file = new File("src/main/groovy/hello.groovy");
        invokeScriptEngine(file, args);
        invokeGroovyShell(file, args);
    }

}
