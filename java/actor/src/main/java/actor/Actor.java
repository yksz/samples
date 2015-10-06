package actor;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public abstract class Actor {
    private final BlockingQueue<Object> mailbox = new LinkedBlockingQueue<>();

    public void tell(Object message) throws InterruptedException {
        mailbox.put(message);
        ActorSystem.getPool().submit(() -> {
            try {
                onReceive(mailbox.take());
            } catch (InterruptedException ignore) {
            }
        });
    }

    public abstract void onReceive(Object message);
}
