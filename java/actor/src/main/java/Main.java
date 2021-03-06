import actor.Actor;
import actor.ActorSystem;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        ActorSystem.assign("/path/actor1", new Actor() {
            public void onReceive(Object message) {
                System.out.println("actor1: " + message);
            }
        });
        ActorSystem.assign("/path/actor2", new Actor() {
            public void onReceive(Object message) {
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException ignore) {
                }
                System.out.println("actor2: " + message);
            }
        });
        ActorSystem.send("/path/actor1", "foo");
        ActorSystem.send("/path/actor2", "fizz");
        ActorSystem.send("/path/actor1", "bar");
        ActorSystem.send("/path/actor2", "bazz");
        ActorSystem.broadcast("!");
        ActorSystem.shutdown();
    }
}
