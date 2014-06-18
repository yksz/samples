def sort(list) {
    int n = list.size()
    for (i = 0; i < n - 1; i++) {
        def min = i
        for (j = i + 1; j < n; j++) {
            if (list[j] < list[min]) {
                min = j
            }
        }
        Collections.swap(list, i, min)
        println "${i+1}: $list"
    }
}

def list = [20, 6, 55, 74, 3, 45, 13, 87, 46, 30]
sort(list)
println list
