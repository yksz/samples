interface Queue<E> {
    boolean empty()
    boolean enqueue(E data)
    E dequeue()
}

class Ring<E> implements Queue<E> {
    int capacity
    def array
    int size = 0
    int head = 0, tail = 0

    Ring(int capacity) {
        if (capacity <= 0)
            throw new IllegalArgumentException()
        this.capacity = capacity
        array = new E[capacity]
    }

    boolean empty() {
        size == 0
    }

    boolean enqueue(E data) {
        if (size >= capacity) {
            println "enqueue failed: $data"
            return false
        }
        array[tail] = data
        tail = next(tail)
        size++
        println "enqueue: $data"
        return true
    }

    E dequeue() {
        if (empty()) {
            println "dequeue failed"
            return null
        }
        def data = array[head]
        array[head] = null
        head = next(head)
        size--
        println "dequeue: $data"
        return data
    }

    private int next(int i) {
        (i + 1) % capacity
    }
}

def queue = new Ring<Integer>(3)
queue.dequeue()
queue.enqueue(1)
queue.enqueue(2)
queue.enqueue(3)
queue.enqueue(4)
println queue.array
queue.dequeue()
queue.dequeue()
println queue.array
queue.enqueue(5)
queue.enqueue(6)
queue.enqueue(7)
println queue.array
