package dependency.main;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.osgi.framework.BundleActivator;
import org.osgi.framework.BundleContext;

public class Activator implements BundleActivator {

    private static final Log log = LogFactory.getLog(Activator.class);

    public void start(BundleContext context) {
        log.info("Dependency bundle " + context.getBundle().getBundleId() + " has started.");
    }

    public void stop(BundleContext context) {
        log.info("Dependency bundle " + context.getBundle().getBundleId() + " has stopped.");
    }

}
