trait FlyingAbility {
    String fly() { "I'm flying!" }
}
trait SpeakingAbility {
    String speak() { "I'm speaking!" }
}

class Duck implements FlyingAbility, SpeakingAbility {}

def d = new Duck()
assert d.fly() == "I'm flying!"
assert d.speak() == "I'm speaking!"

assert d instanceof FlyingAbility
assert d instanceof SpeakingAbility
assert d instanceof Duck
