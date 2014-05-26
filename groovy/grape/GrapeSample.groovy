@Grapes(
    @Grab(group='commons-logging', module='commons-logging', version='1.1.3')
)
import org.apache.commons.logging.Log
import org.apache.commons.logging.LogFactory

class GrapeSampe {
    private static Log log = LogFactory.getLog(GrapeSampe.class)

    static main(args) {
        log.info("main: args=$args")
    }
}
