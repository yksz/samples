class PriorityQueue<E> {
    def heap

    PriorityQueue(int capacity) {
        heap = new Heap(capacity)
    }

    boolean empty() {
        heap.empty()
    }

    boolean enqueue(E data) {
        heap.insert(data)
    }

    E dequeue() {
        heap.delete()
    }

    void print() {
        heap.print()
    }
}

class Heap<E> {
    int capacity
    def array // array[0] is not used
    int size = 0

    Heap(int capacity) {
        if (capacity <= 0)
            throw new IllegalArgumentException()
        this.capacity = capacity
        array = new E[capacity + 1]
    }

    boolean empty() {
        size == 0
    }

    boolean insert(E data) {
        if (size >= capacity) {
            println "insert failed: $data"
            return false
        }
        size++
        array[size] = data
        upheap(size)
        println "insert: $data"
        return true
    }

    E delete() {
        if (empty()) {
            println "delete failed"
            return null
        }
        def data = array[1]
        array[1] = array[size]
        array[size] = null
        size--
        downheap(1)
        println "delete: $data"
        return data
    }

    private void upheap(int index) {
        def data = array[index]
        while (index > 1) {
            int parent = index / 2
            if (array[parent] <= data) {
                break
            }
            array[index] = array[parent]
            index = parent
        }
        array[index] = data
    }

    private void downheap(int index) {
        def data = array[index]
        while (index <= size / 2) {
            int child = index * 2
            if (child + 1 <= size && array[child] > array[child + 1]) {
                child++
            }
            if (array[child] >= data) {
                break
            }
            array[index] = array[child]
            index = child
        }
        array[index] = data
    }

    void print() {
        int height = (int) (Math.log(size)/Math.log(2) + 0.5) + 1
        for (i in 1..height) {
            int begin = Math.pow(2, i-1)
            int end = Math.pow(2, i)
            for (int j = begin; j < end && j <= size; j++) {
                if (i == height) {
                    print ' '
                    print array[j]
                } else {
                    if (j == begin) {
                        print ' ' * (height - i) * 2
                    }
                    print array[j]
                    print '   '
                }
            }
            println()
        }
    }
}

def queue = new PriorityQueue<Integer>(6)
queue.dequeue()
queue.enqueue(9)
queue.enqueue(8)
queue.enqueue(7)
queue.enqueue(6)
queue.print()
queue.dequeue()
queue.dequeue()
queue.print()
queue.enqueue(5)
queue.enqueue(4)
queue.enqueue(3)
queue.enqueue(2)
queue.enqueue(1)
queue.print()
