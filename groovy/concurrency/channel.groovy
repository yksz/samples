// Golang channel ?

import java.util.concurrent.ArrayBlockingQueue

class Channel {
    def queue

    Channel() {
        this(1)
    }

    Channel(int buffer) {
        queue = new ArrayBlockingQueue(buffer)
    }

    def send(msg) {
        queue.put(msg)
    }

    def receive() {
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
