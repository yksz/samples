class Test {
    String method() {
        return "method"
    }
    String methodWithParam(String param) {
        return "method with param"
    }
    static String staticMethod() {
        return "static method"
    }
}

def mock = [
    method:{ "mock method" },
    methodWithParam:{ param -> "mock method with param: " + param }
//  staticMethod:{ "mock static method" } // error
] as Test
assert mock.method() == "mock method"
assert mock.methodWithParam("abc") == "mock method with param: abc"
