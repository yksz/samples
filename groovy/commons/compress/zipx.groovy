@Grapes([
    @Grab(group='org.apache.commons', module='commons-compress', version='1.8.1'),
    @Grab(group='commons-io', module='commons-io', version='2.4')
])
import org.apache.commons.compress.archivers.zip.*
import org.apache.commons.io.*

def extract(String src, String dst) {
    def input = new ZipArchiveInputStream(new FileInputStream(src))
    try {
        def entry
        while ((entry = input.getNextEntry()) != null) {
            def file = new File(FilenameUtils.getFullPath(dst) + entry.name)
            if (entry.isDirectory()) {
                FileUtils.forceMkdir(file)
            } else {
                FileUtils.forceMkdir(file.parentFile)
                def output = new FileOutputStream(file)
                try {
                    IOUtils.copy(input, output)
                } finally {
                    output.close()
                }
            }
        }
    } finally {
        input.close()
    }
}


if (args.length < 1) {
    println 'usage: zipx.groovy <filepath>'
    System.exit(1)
}
def src = args[0]
def dst = FilenameUtils.removeExtension(src)
long start = System.currentTimeMillis()
extract(src, dst)
long stop = System.currentTimeMillis()
println "${(stop - start) / 1000} sec"
