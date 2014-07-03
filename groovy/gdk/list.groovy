assert [] instanceof ArrayList == true

// 1. Collection or Iterable
// - loop
x = 1
for (i in [1,2,3]) assert i == x++
x = 1
[1,2,3].each { assert it == x++ }
x = 3
[1,2,3].reverseEach { assert it == x-- }

// - operator
assert [1,2,3] + 4    == [1,2,3,4]
assert [1,2,3] + [4]  == [1,2,3,4]
assert [1,2,3] - 3    == [1, 2]
assert [1,2,3] - [3]  == [1, 2]
assert [1,2,3] * 2    == [1,2,3,1,2,3]
assert [1,2,3] << 4   == [1,2,3,4]
assert [1,2,3] << [4] == [1,2,3,[4]]
assert [1,*[2,3]]     == [1,2,3]

// - util
assert [1,3,3].count(3)  == 2
assert [1,2,3].join(",") == "1,2,3"
assert [1,2,3].max()     == 3
assert [1,2,3].min()     == 1
assert [1,2,3].sum()     == 6
assert [3,2,1].sort()    == [1,2,3]
assert [1,3,3].unique()  == [1,3]

// - closure
assert [1,2,3].any { it > 2 }              == true  // or
assert [1,2,3].every { it > 2 }            == false // and
assert [1,2,3].collect { it + 1 }          == [2,3,4]
assert [1,2,3,4].find { it % 2 == 0 }      == 2
assert [1,2,3,4].findAll { it % 2 == 0 }   == [2,4]
assert [1,2,3].groupBy { it % 2 }          == [1:[1,3], 0:[2]]
assert [1,2,3].inject { acc, v -> acc + v} == (((0+1)+2)+3)
assert [1,2,3].split { it % 2 == 0 }       == [[2],[1,3]]

// - regexp
assert ["ab","ac","bc"].find { it =~ /a+/ }    == "ab"
assert ["ab","ac","bc"].findAll { it =~ /a+/ } == ["ab","ac"]
assert ["ab","ac","bc"].grep(~/a.+/ )          == ["ab","ac"]

// - other
assert [1,2,3].disjoint([3,4,5])    == false
assert [1,2,3].disjoint([4,5,6])    == true
assert [1,2,3,4].intersect([3,4,5]) == [3,4]
assert [1,[2,3]].flatten()          == [1,2,3]

// 2. List
assert [1,2,3].first() == 1
assert [1,2,3].last()  == 3
assert [1,2,3].head()  == 1
assert [1,2,3].tail()  == [2,3]
assert [1,2,3].drop(1) == [2,3]
assert [1,2,3].drop(3) == []
assert [1,2,3,4,5].collate(2) == [[1,2],[3,4],[5]]
assert [1,2,3].permutations() == [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]] as Set
assert [1,2,3].subsequences() == [[1,2,3],[1,2],[1,3],[2,3],[1],[2],[3]] as Set
assert [1,2,3].take(1) == [1]
assert [1,2,3].take(3) == [1,2,3]
assert [1,2,3].reverse() == [3,2,1]
assert [['a','b'],[1,2]].transpose() == [['a',1],['b',2]]

def list = [1,2,3]
assert list[0] == 1
assert list[-1] == 3
assert list[1..2] == [2,3]
assert list.pop() == 3 && list == [1,2]
assert list.push(3) && list == [1,2,3]
