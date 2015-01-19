package hello;

import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.*;
import org.springframework.context.support.GenericGroovyApplicationContext;

@Configuration
@ComponentScan
public class Application {
    @Bean
    MessageService mockMessageService() {
        return new MessageService() {
            public String getMessage() {
                return "Hello World!";
            }
        };
    }

    public static void main(String[] args) {
        {
            ApplicationContext context = new AnnotationConfigApplicationContext(Application.class);
            MessagePrinter printer = context.getBean(MessagePrinter.class);
            printer.printMessage();
        }
        {
            ApplicationContext context = new GenericGroovyApplicationContext("context.groovy");
            MessagePrinter printer = context.getBean("printer", MessagePrinter.class);
            printer.printMessage();
        }
    }
}
