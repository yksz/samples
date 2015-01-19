/**
 * This is a Hoge class.
 *
 * @see java.lang.Class
 * @since 1.0
 */
public class Hoge {

    /**
     * Converts a {@code String} object to an {@code Integer} object.
     *
     * @param s a {@code String} object
     * @return an {@code Integer} object
     * @deprecated
     */
    Integer toInteger(String s) {
        return Integer.valueOf(s);
    }

    /**
     * Returns a string representation of the object.
     *
     * @return a string
     */
    @Override
    public String toString() {
        return "hoge";
    }

}
