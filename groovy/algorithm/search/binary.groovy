def search(list, target) {
    int low = 0, high = list.size() - 1
    int middle
    while (low <= high) {
        middle = (low + high) / 2
        if (list[middle] == target) {
            return middle
        } else if (list[middle] < target) {
            low = middle + 1
        } else {
            high = middle - 1
        }
    }
    return -1
}

def list = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19]
assert search(list, 7) == 3
assert search(list, 2) == -1
