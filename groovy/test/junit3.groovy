import groovy.util.GroovyTestCase

class StringTest extends GroovyTestCase {
    void testSubstring() {
        assertEquals("happy", "unhappy".substring(2))
    }

    void testNegativeNumber() {
        shouldFail(IndexOutOfBoundsException) {
            "unhappy".substring(-1)
        }
    }
}
