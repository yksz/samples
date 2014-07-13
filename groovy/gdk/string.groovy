def str = 'abc'
assert str[0] == 'a'
assert str[-1] == 'c'
assert str[1..2] == 'bc'

// - loop
x = 1
for (i in '123') assert i == "${x++}"
x = 1
'123'.each { assert it == "${x++}" }
x = 1
'1\n2'.eachLine { assert it == "${x++}" }

// - operator
assert 'abc' + 'd' == 'abcd'
assert 'abc' - 'b' == 'ac'
assert 'abc' *  2  == 'abcabc'
assert ('abc' << 'd').toString() == 'abcd'
s = 'abc'; s++
assert s == 'abd'
s = 'abc'; s--
assert s == 'abb'

// - closure
assert 'abc'.collectReplacements { it == 'b' ? 'B' : null } == 'aBc'

// - regexp

// - other
assert 'abc def'.capitalize() == 'Abc def'
assert 'abc'.center(6)        == ' abc  '
assert 'abc'.center(6, '+')   == '+abc++'
assert 'abca'.count('a')      == 2
assert 'abc'.bytes.encodeBase64().toString().decodeBase64() == 'abc'.bytes
assert 'abc'.bytes.encodeHex().toString().decodeHex()       == 'abc'.bytes
assert '\t'.expand()  == '        '
assert '\t'.expand(4) == '    '
assert ' \t\n\r'.isAllWhitespace()
assert 'abc'.padLeft(5)       == '  abc'
assert 'abc'.padLeft(5, '*')  == '**abc'
assert 'abc'.padRight(5)      == 'abc  '
assert 'abc'.padRight(5, '#') == 'abc##'
assert 'a\nb\nc'.readLines()  == ['a','b','c']
assert 'a b c'.split()        == ['a','b','c']
