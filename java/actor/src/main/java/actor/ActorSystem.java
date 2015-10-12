package actor;

import java.util.Map;
import java.util.TreeMap;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.TimeUnit;

public class ActorSystem {
    private static final Map<String, Actor> actors = new TreeMap<>();
    private static final ForkJoinPool pool = new ForkJoinPool();

    public static synchronized void assign(String address, Actor actor) {
        actors.put(address, actor);
    }

    public static synchronized void remove(String address) {
        actors.remove(address);
    }

    public static synchronized void send(String address, Object message)
            throws InterruptedException {
        Actor actor = actors.get(address);
        if (actor != null) {
            actor.tell(message);
        }
    }

    public static synchronized void shutdown() throws InterruptedException {
        pool.shutdown();
        pool.awaitTermination(10, TimeUnit.SECONDS);
    }

    static synchronized void dispatch(Runnable task) {
        pool.submit(task);
    }
}
