@Grapes([
    @Grab(group='org.apache.commons', module='commons-compress', version='1.8.1'),
    @Grab(group='commons-io', module='commons-io', version='2.4')
])
import org.apache.commons.compress.archivers.zip.*
import org.apache.commons.io.*
import org.apache.commons.io.filefilter.*

def compress(String src, String dst) {
    def output = new ZipArchiveOutputStream(new FileOutputStream(dst))
    try {
        def srcFile = new File(src)
        def base = srcFile.parentFile.absolutePath
        if (srcFile.isDirectory()) {
            def files = FileUtils.listFilesAndDirs(srcFile, TrueFileFilter.TRUE, TrueFileFilter.TRUE)
            for (file in files) {
                if (file.isDirectory()) {
                    putDir(output, file, base)
                } else {
                    putFile(output, file, base)
                }
            }
        } else {
            putFile(output, srcFile)
        }
        output.flush()
    } finally {
        output.close()
    }
}

private def putFile(output, file, base) {
    def name = file.absolutePath.substring(base.length() + 1)
    def entry = new ZipArchiveEntry(name)
    entry.size = file.length()
    output.putArchiveEntry(entry)
    def input = new FileInputStream(file)
    try {
        IOUtils.copy(input, output)
    } finally {
        input.close()
        output.closeArchiveEntry()
    }
}

private def putDir(output, dir, base) {
    def name = dir.absolutePath.substring(base.length() + 1)
    output.putArchiveEntry(new ZipArchiveEntry(name + '/'))
    output.closeArchiveEntry()
}


if (args.length < 1) {
    println 'usage: zipc.groovy <filepath>'
    System.exit(1)
}
def src = args[0]
def dst = src + '.zip'
long start = System.currentTimeMillis()
compress(src, dst)
long stop = System.currentTimeMillis()
println "${(stop - start) / 1000} sec"
