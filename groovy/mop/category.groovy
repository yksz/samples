class StringCategory1 {
    static String lower(String self) {
        return self.toLowerCase()
    }
}

@Category(String)
class StringCategory2 {
    String upper() {
        return this.toUpperCase()
    }
}

use(StringCategory1, StringCategory2) {
    assert "test" == "TeSt".lower()
    assert "TEST" == "TeSt".upper()
}
