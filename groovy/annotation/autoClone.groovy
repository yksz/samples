import groovy.transform.*

@AutoClone
class Person {
    String first, last
    List favItems
    Date since
}

def p1 = new Person(first:'John', last:'Smith', favItems:['ipod', 'shiraz'], since:new Date())
def p2 = p1.clone()
assert p1.first == p2.first
assert p1.last == p2.last
assert p1.favItems == p2.favItems
assert p1.since == p2.since
