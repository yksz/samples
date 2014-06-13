class NewString {
    @Delegate String str

    NewString(String str) {
        this.str = str
    }
}

def newstr = new NewString("abc")
assert newstr.toUpperCase() == "ABC"
