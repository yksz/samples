package newmath

// Sum a slice of int
func Sum(slice []int) int {
	sum := 0
	for _, v := range slice {
		sum += v
	}
	return sum
}
