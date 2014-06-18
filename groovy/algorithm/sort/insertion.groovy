def sort(list) {
    int n = list.size()
    for (i = 1; i < n; i++) {
        for (j = i; j > 0 && list[j-1] > list[j]; j--) {
            if (list[j-1] > list[j]) {
                Collections.swap(list, j-1, j)
            }
        }
        println "$i: $list"
    }
}

def list = [20, 6, 55, 74, 3, 45, 13, 87, 46, 30]
sort(list)
println list
