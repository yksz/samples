package simple;

import org.osgi.framework.BundleActivator;
import org.osgi.framework.BundleContext;

public class Activator implements BundleActivator {

    public void start(BundleContext context) {
        System.out.println("Simple bundle " + context.getBundle().getBundleId() + " has started.");
    }

    public void stop(BundleContext context) {
        System.out.println("Simple bundle " + context.getBundle().getBundleId() + " has stopped.");
    }

}
