def sort(array) {
    if (array.size() == 1)
        return array
    int middle = array.size() / 2
    def array1 = array[0..<middle]
    def array2 = array[middle..<array.size()]
    return merge(sort(array1), sort(array2))
}

private def merge(array1, array2) {
    def merge = new ArrayList(array1.size() + array2.size())
    int index = 0, i1 = 0, i2 = 0
    while (i1 < array1.size() && i2 < array2.size()) {
        if (array1[i1] < array2[i2]) {
            merge[index] = array1[i1]
            i1++
        } else {
            merge[index] = array2[i2]
            i2++
        }
        index++
    }
    while (i1 < array1.size()) {
        merge[index] = array1[i1]
        i1++
    }
    while (i2 < array2.size()) {
        merge[index] = array2[i2]
        i2++
    }
    return merge
}

def array = [55, 13, 3, 45, 74, 87, 46, 30]
println sort(array)
