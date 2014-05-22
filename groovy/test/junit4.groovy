import org.junit.Test
import static org.junit.Assert.*

class StringTest {
    @Test
    void substring() {
        assertEquals("happy", "unhappy".substring(2))
    }

    @Test(expected=IndexOutOfBoundsException)
    void negativeNumber() {
        "unhappy".substring(-1)
    }
}
