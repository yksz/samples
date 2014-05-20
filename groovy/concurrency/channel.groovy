// Golang channel ?

import java.util.concurrent.ArrayBlockingQueue

class Channel {
    def queue

    Channel() {
        queue = new ArrayBlockingQueue(1)
    }

    def send(msg) {
        queue.put(msg)
    }

    def receive(msg) {
        return queue.take()
    }

    def leftShift(msg) {
        send(msg)
    }
}


def chan = new Channel()
Thread.start {
    chan.send "Hello"
}
Thread.start {
    chan << "World"
}
println chan.receive()
println chan.receive()
