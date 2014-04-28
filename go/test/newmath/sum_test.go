package newmath

import (
	"reflect"
	"testing"
)

func assert(t *testing.T, expected, actual interface{}) {
	if !reflect.DeepEqual(expected, actual) {
		t.Errorf("(expected, actual) = (%v, %v)\n", expected, actual)
	}
}

func TestSum1(t *testing.T) {
	slice := []int{1, 2, 3, 4, 5}
	sum := Sum(slice)
	assert(t, 15, sum)
}

func TestSum2(t *testing.T) {
	sum := Sum(nil)
	assert(t, 0, sum)
}
