import lib.TestLibrary;

public class JNIMain {

    static {
        System.loadLibrary("lib_TestLibrary");
    }

    public static void main(String[] args) {
        TestLibrary testlib = new TestLibrary();
        testlib.println("print by testlib");
    }

}
