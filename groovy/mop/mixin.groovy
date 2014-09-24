class FlyingAbility {
    def fly() { "fly" }
}

class DivingAbility {
    def dive() { "dive" }
}

class Plane {}
Plane.mixin(FlyingAbility)

@Mixin(DivingAbility)
class Submarine {}

assert new Plane().fly() == "fly"
assert new Submarine().dive() == "dive"

assert !(new Plane() instanceof FlyingAbility)
assert !(new Submarine() instanceof DivingAbility)
