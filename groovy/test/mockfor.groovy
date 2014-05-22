import groovy.mock.interceptor.MockFor

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

def mock = new MockFor(Test)
mock.demand.method { "mock method" }
mock.demand.with {
    methodWithParam { param -> "mock method with param: $param" }
    staticMethod { "mock static method" }
}
mock.use {
    def test = new Test()
    assert test.method() == "mock method"
    assert test.methodWithParam("abc") == "mock method with param: abc"
    assert test.staticMethod() == "mock static method"
}
