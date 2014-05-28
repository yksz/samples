assert [:] instanceof HashMap == true

//  - operator
assert [a:1,b:2] + [c:3]  == [a:1,b:2,c:3]
assert [a:1,b:2] - [b:2]  == [a:1]
assert [a:1,b:2] << [c:3] == [a:1,b:2,c:3]
assert [a:1,*:[b:2,c:3]]  == [a:1,b:2,c:3]

//  - closure
assert [a:1,b:2].any { it.value > 1 }                    == true  // or
assert [a:1,b:2].every { it.value > 1 }                  == false // and
assert [a:1,b:2].collect { k,v -> k * v }                == ["a","bb"]
assert [a:1,b:2].collectEntries { k,v -> [v, k] }        == [1:"a",2:"b"]
assert [a:1,bc:2].collectMany { it.key.toList() }        == ["a","b","c"]
assert [a:1,b:2,c:3].count { it.value > 1 }              == 2
assert [a:1,b:2,c:3].countBy { it.value % 2 }            == [0:1,1:2]
assert [a:1,b:2,c:3].find { it.value % 2 != 0 }.key      == "a"
assert [a:1,b:2,c:3].findAll { it.value % 2 != 0 }       == [a:1,c:3]
assert [a:1,b:2].groupBy { it.value % 2 }                == [0:[b:2],1:[a:1]]
assert [a:1,b:2].groupEntriesBy { it.value % 2 }[0]*.key == ["b"]
assert [a:1,b:2].inject([]) { list, k, v -> list + [k] } == ["a","b"]

//  - other
assert [a:1,b:2,c:3].drop(1) == [b:2,c:3]
assert [a:1,b:2,c:3].drop(3) == [:]
assert [a:1,b:2].get("c", 3) == 3
assert [a:1,b:2,c:3].intersect([b:2,c:3,d:4]) == [b:2,c:3]
