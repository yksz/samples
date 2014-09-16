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
x = 1
'1a2b3c'.eachMatch(/\d/) { assert it == "${x++}" }

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
assert 'a b c'.find(/\w/) == 'a'
'a b c'.find(/\w/) { assert it == 'a' }
assert 'a b c'.findAll(/\w/) == ['a', 'b', 'c']
assert 'a b c'.findAll(/\w/) { it.toUpperCase() } == ['A', 'B', 'C']
assert 'abc'.matches(~/[a-c]+/) == true
assert 'hello'.replaceAll('l', 'L') == 'heLLo'
assert 'hello'.replaceAll('l') { it[0].toUpperCase() } == 'heLLo'
assert 'hello'.replaceFirst('l', 'L') == 'heLlo'
assert 'hello'.replaceFirst('l') { it[0].toUpperCase() } == 'heLlo'
s = 'a'; x = 1
'a:1\nb:2\nc:3'.splitEachLine(/:/) { assert it[0] == s++; assert it[1] == "${x++}" }

// - other
assert 'abc def'.capitalize()         == 'Abc def'
assert 'abc'.center(6)                == ' abc  '
assert 'abc'.center(6, '+')           == '+abc++'
assert 'abc'.contains('ab')           == true
assert 'abca'.count('a')              == 2
assert ' \t'.expand()                 == '        '
assert ' \t'.expand(4)                == '    '
assert ' \t\n\r'.isAllWhitespace()    == true
assert 'a\rb\nc\r\n'.normalize()      == 'a\nb\nc\n'
assert 'abc'.padLeft(5)               == '  abc'
assert 'abc'.padLeft(5, '*')          == '**abc'
assert 'abc'.padRight(5)              == 'abc  '
assert 'abc'.padRight(5, '#')         == 'abc##'
assert 'a\nb\nc'.readLines()          == ['a','b','c']
assert 'abc'.reverse()                == 'cba'
assert 'a b c'.split()                == ['a','b','c']
assert '   a\n  b\n c'.stripIndent()  == '  a\n b\nc'
assert '#a\n#b\n#c'.stripIndent(1)    == 'a\nb\nc'
assert 'a\n |b\n |c'.stripMargin()    == 'a\nb\nc'
assert 'a\n *b\n *c'.stripMargin('*') == 'a\nb\nc'
assert 'a b c'.tokenize()             == ['a','b','c']
assert 'a:b:c'.tokenize(':')          == ['a','b','c']
assert 'hello'.tr('a-z', 'A-Z')       == 'HELLO'
assert '         '.unexpand()         == '\t '
assert '     '.unexpand(4)            == '\t '

assert 'abc'.bytes.encodeBase64().toString().decodeBase64() == 'abc'.bytes
assert 'abc'.bytes.encodeHex().toString().decodeHex()       == 'abc'.bytes
