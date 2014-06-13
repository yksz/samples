import java.lang.annotation.ElementType
import java.lang.annotation.Retention
import java.lang.annotation.RetentionPolicy
import java.lang.annotation.Target

@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.METHOD)
@interface Foo {
    String value()
}

class Bar {
    @Foo('hello')
    void bar() {
    }
}

Bar.class.getDeclaredMethods().each { method ->
    def annotation = method.getAnnotation(Foo)
    if (annotation) {
        println annotation
        println method
    }
}
