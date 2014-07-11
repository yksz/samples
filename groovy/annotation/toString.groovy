import groovy.transform.*

@ToString(includeNames=true, includeFields=true)
class Hoge {
    def foo
    private def bar
}

def hoge = new Hoge(foo:0, bar:1)
assert hoge.toString() == "Hoge(foo:0, bar:1)"
