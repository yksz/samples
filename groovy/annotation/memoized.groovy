import groovy.transform.*

class MemoizedExample {
    @Memoized
    int sum(int n1, int n2) {
        println "$n1 + $n2 = ${n1 + n2}"
        n1 + n2
    }
}

def instance = new MemoizedExample()
println instance.sum(1, 2)
println instance.sum(1, 2)
println instance.sum(2, 3)
println instance.sum(2, 3)
