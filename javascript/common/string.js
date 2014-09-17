var str = 'abc';
console.assert(str[0] == 'a');

// - loop
var str = '123';
var x = 1;
for (var i = 0; i < str.length; i++) {
  console.assert(str[i] == x++);
}

// - operator
console.assert('abc' + 'd' == 'abcd');
console.assert('123' == 123);
console.assert('123' !== 123);

// - method
console.assert('abc'.charAt(0) == 'a');
console.assert('abc'.charCodeAt(0) == 97);
console.assert('abc'.concat('d', 'ef') == 'abcdef');
console.assert('aba'.indexOf('a') == 0);
console.assert('aba'.indexOf('A') == -1);
console.assert('aba'.lastIndexOf('a') == 2);
console.assert('aba'.lastIndexOf('A') == -1);
'ABCDEFGabcdefg'.match(/[A-C]/gi); // => ['A','B','C','a','b','c']
console.assert('a b c'.replace(/\s/g, ',') == 'a,b,c');
console.assert('a b c'.search(/\s/) == 1);
console.assert('a b c'.search(/\d/) == -1);
console.assert('abc'.slice(1, -1) == 'b');
'a b c'.split(/\s/); // => ['a','b','c']
console.assert('abc'.substr(1, 1) == 'b');
console.assert('abc'.substring(1, 2) == 'b');
console.assert('ABC'.toLowerCase() == 'abc');
console.assert('abc'.toUpperCase() == 'ABC');
console.assert(' abc  '.trim() == 'abc');
