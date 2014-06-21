def sort(array) {
    quicksort(array, 0, array.size() - 1)
}

def quicksort(array, left, right) {
    if (left >= right)
        return
    int i = left, j = right
    int middle = (left + right) / 2
    def pivot = median(array[left], array[right], array[middle])
    while (true) {
        while (array[i] < pivot)
            i++
        while (pivot < array[j])
            j--
        if (i > j)
            break
        Collections.swap(array, i, j)
        i++
        j--
    }
    quicksort(array, left, j)
    quicksort(array, i, right)
}

def median(x, y, z) {
    if (x < y)
        if (y < z)
            return y
        else if (z < x)
            return x
        else
            return z
    else
        if (z < y)
            return y
        else if (x < z)
            return x
        else
            return z
}

def array = [55, 3, 74, 20, 13, 87, 46, 30]
sort(array)
println array
