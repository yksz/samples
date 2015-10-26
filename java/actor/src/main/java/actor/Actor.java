package actor;

public abstract class Actor {
    public void tell(final Object message) throws InterruptedException {
        ActorSystem.dispatch(() -> {
            onReceive(message);
        });
    }

    public abstract void onReceive(Object message);
}
