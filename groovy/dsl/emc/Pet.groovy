import groovy.transform.ToString

@ToString(includeNames=true)
class Pet {
    def name

    def name(String name) {
        this.name = name
    }

    def say(Closure closure) {
        print "$name says "
        closure()
    }
}
