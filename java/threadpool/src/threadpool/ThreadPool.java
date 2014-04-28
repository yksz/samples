package threadpool;

public class ThreadPool extends AbstractThreadPool<Runnable> {

    public ThreadPool(int maxQueueSize, int numberOfThreads) {
        super(maxQueueSize, numberOfThreads);
    }

    @Override
    protected void execute(Runnable job) {
        job.run();
    }

}
