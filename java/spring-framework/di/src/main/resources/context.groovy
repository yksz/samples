import hello.*

beans {
    service(MessageServiceImpl) {}
    printer MessagePrinter, service
}
