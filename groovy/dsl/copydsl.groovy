class CopyDSL {
    String from
    String into

    static def copy(Closure closure) {
        CopyDSL dsl = new CopyDSL()
        closure.delegate = dsl
        closure()
        println "copy: from=$dsl.from, into=$dsl.into"
    }

    def from(String from) {
        this.from = from
    }

    def into(String into) {
        this.into = into
    }
}

def copy(Closure closure) {
    CopyDSL.copy(closure)
}

CopyDSL.copy {
    from "a.txt"
    into "b.txt"
}
copy {
    from "c.txt"
    into "d.txt"
}
