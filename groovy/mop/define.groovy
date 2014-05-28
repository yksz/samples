class Empty { String name }
Empty.metaClass.constructor << { String arg -> println "constructor: $arg"; new Empty(name:arg) }
Empty.metaClass.static.myMethod << { args -> "static myMethod" }
Empty.metaClass.myMethod << { args -> "myMethod" }

def obj1 = new Empty("obj1")
assert obj1.myMethod() == "myMethod"
assert Empty.myMethod() == "static myMethod"

Empty.metaClass.constructor = { String arg -> println "replaced constructor: $arg"; new Empty(name:arg) }
def obj2 = new Empty("obj2")
obj2.metaClass {
    myProperty = "myProperty"
    myMethod = { args -> "replaced myMethod" }
}
assert obj2.myProperty == "myProperty"
assert obj2.myMethod() == "replaced myMethod"


Integer.metaClass.define {
    reverse { return delegate.toString().reverse() as Integer }
}
assert 123456.reverse() == 654321
