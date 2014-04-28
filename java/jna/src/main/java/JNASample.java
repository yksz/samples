import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Platform;

public class JNASample {

    public interface CLibrary extends Library {
        CLibrary clib = (CLibrary) Native.loadLibrary(Platform.isWindows() ? "msvcrt" : "c", CLibrary.class);
        void printf(String format, Object... args);
    }

    public interface TestLibrary extends Library {
        TestLibrary testlib = (TestLibrary) Native.loadLibrary("test", TestLibrary.class);
        void println(String str);
    }

    public static void main(String[] args) {
        CLibrary.clib.printf("print by clib\n");
        TestLibrary.testlib.println("print by testlib");
    }

}
