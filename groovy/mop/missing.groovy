class Foo {
    def methodMissing(String name, Object args) {
        println "name=$name, args=$args"
    }
}
Foo.metaClass.propertyMissing { name, value ->
    println "name=$name, value=$value"
}

def foo = new Foo()
foo.method("a")
foo.property = "b"
