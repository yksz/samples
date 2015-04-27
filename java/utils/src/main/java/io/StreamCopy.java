package io;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.function.BiConsumer;

public class StreamCopy {
    public static void copy(InputStream in, OutputStream out) throws IOException {
        BufferedInputStream bin = new BufferedInputStream(in);
        BufferedOutputStream bout = new BufferedOutputStream(out);
        try {
            byte[] buf = new byte[8192];
            int len = 0;
            while ((len = bin.read(buf)) != -1)
                bout.write(buf, 0, len);
            bout.flush();
        } finally {
            try {
                if (bin != null)
                    bin.close();
            } catch (IOException e) {
            }
            try {
                if (bout != null)
                    bout.close();
            } catch (IOException e) {
            }
        }
    }

    public static void copyByTryWithResources(InputStream in, OutputStream out) throws IOException {
        try (BufferedInputStream bin = new BufferedInputStream(in);
                BufferedOutputStream bout = new BufferedOutputStream(out)) {
            byte[] buf = new byte[8192];
            int len;
            while ((len = bin.read(buf)) != -1)
                bout.write(buf, 0, len);
            bout.flush();
        }
    }

    private static void testCopy(BiConsumer<InputStream, OutputStream> func) {
        String str = "foobar";
        ByteArrayInputStream in = new ByteArrayInputStream(str.getBytes());
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        func.accept(in, out);
        assert str.equals(out.toString());
    }

    public static void main(String[] args) {
        testCopy((in, out) -> {
            try {
                copy(in, out);
            } catch (IOException e) {
                e.printStackTrace();
            }
        });
        testCopy((in, out) -> {
            try {
                copyByTryWithResources(in, out);
            } catch (IOException e) {
                e.printStackTrace();
            }
        });
    }
}
