def sort(list) {
    int n = list.size()
    for (i = 0; i < n - 1; i++) {
        for (j = 1; j < n - i; j++) {
            if (list[j-1] > list[j]) {
                Collections.swap(list, j-1, j)
            }
        }
        println "${i+1}: $list"
    }
}

def list = [20, 6, 55, 74, 3, 45, 13, 87, 46, 30]
sort(list)
println list
