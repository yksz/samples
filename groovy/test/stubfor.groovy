import groovy.mock.interceptor.StubFor

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

def stub = new StubFor(Test)
stub.demand.method { "stub method" } // not use
stub.demand.with {
    methodWithParam { param -> "stub method with param: $param" }
    staticMethod { "stub static method" }
}
stub.use {
    def test = new Test()
    assert test.staticMethod() == "stub static method" // call in out of order
    assert test.methodWithParam("abc") == "stub method with param: abc" // call in out of order
}
