import java.util.concurrent.atomic.AtomicInteger;

import threadpool.ThreadPool;

public class ThreadPoolSample {

    public static void main(String[] args) {
        final AtomicInteger count = new AtomicInteger(0);
        Runnable job = new Runnable() {
            @Override
            public void run() {
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                }
                System.out.println("count: " + count.addAndGet(1));
            }
        };

        ThreadPool threadPool = new ThreadPool(1, 2);
        threadPool.start();
        threadPool.dispatch(job);
        threadPool.dispatch(job);
        threadPool.dispatch(job);
        threadPool.stop();
    }

}
