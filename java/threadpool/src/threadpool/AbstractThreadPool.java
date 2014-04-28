package threadpool;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

public abstract class AbstractThreadPool<T> {

    private static final Object STOP = new Object();

    private BlockingQueue<T> queue;
    private Thread[] threads;

    private boolean isStarted;

    public AbstractThreadPool(int maxQueueSize, int numberOfThreads) {
        if (maxQueueSize < 1)
            throw new IllegalArgumentException("maxQueueSize is less than 1: " + maxQueueSize);
        if (numberOfThreads < 1)
            throw new IllegalArgumentException("numberOfThreads is less than 1: " + numberOfThreads);

        queue = new ArrayBlockingQueue<T>(maxQueueSize);

        threads = new Thread[numberOfThreads];
        for (int i = 0; i < threads.length; i++)
            threads[i] = new WorkerThread();
    }

    public synchronized void start() {
        if (isStarted)
            throw new IllegalStateException("threads have been already started");

        isStarted = true;

        for (Thread thread : threads)
            thread.start();
    }

    @SuppressWarnings("unchecked")
    public synchronized void stop() {
        if (!isStarted)
            throw new IllegalStateException("threads have not been started");

        for (int i = 0; i < threads.length; i++)
            dispatch((T) STOP);

        isStarted = false;

        for (Thread thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }

    public synchronized void dispatch(T job) {
        if (job == null)
            throw new NullPointerException("job is null");
        if (!isStarted)
            throw new IllegalStateException("this pool has not been started yet");

        try {
            queue.put(job);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    public synchronized boolean isStarted() {
        return isStarted;
    }

    private class WorkerThread extends Thread {

        @Override
        public void run() {
            try {
                while (true) {
                    T job = queue.take();
                    if (job == STOP)
                        return;
                    else
                        execute(job);
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }

    }

    protected abstract void execute(T job);

}
