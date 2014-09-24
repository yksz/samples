trait Trait1 {
    def trait1() { 'trait1' }
}
trait Trait2 {
    def trait2() { 'trait2' }
}

def s1 = new String() as Trait1
def s2 = new String().withTraits(Trait1, Trait2)
assert s1.trait1() == 'trait1'
assert s2.trait1() == 'trait1'
assert s2.trait2() == 'trait2'
