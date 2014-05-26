package foo

class Foo {
    void show() {
        println "Foo"
        new foo.bar.Bar().show()
    }
}
