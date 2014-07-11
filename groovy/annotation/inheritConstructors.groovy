import groovy.transform.*

@InheritConstructors
class NewException extends Exception {}

try {
    throw new NewException("new exception")
} catch (e) {
    assert e.message == "new exception"
}
