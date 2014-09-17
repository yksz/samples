var array = [1,2,3];
console.assert(array[0] == 1);
console.assert(array[3] == undefined);
array[9] = '';
console.assert(array[9] == '' && array.length == 10);

// - loop
var array = [1,2,3];
var x = 1;
for (var i = 0; i < array.length; i++) {
  console.assert(array[i] == x++);
}
var array = [1,2,3];
var x = 1;
array.forEach(function(e, i, a) {
  console.assert(e == x++);
});

// - operator
console.assert([1,2,3] != [1,2,3]);
console.assert([1,2,3] !== [1,2,3]);

// - Array
console.assert(Array.isArray([1,2,3]));

// - mutator
var array = [1,2,3];
array.pop(); // => 3, array => [1,2]
var array = [1,2,3];
array.push(4); // => 4, array => [1,2,3,4]
var array = [1,2,3];
array.reverse(); // => [3,2,1], array => [3,2,1]
var array = [1,2,3];
array.shift(); // => 1, array => [2,3]
var array = [3,2,1];
array.sort(function(a, b) { return a - b; }); // => [1,2,3], array => [1,2,3]
var array = [1,2,3];
array.splice(3, 0, 4); // => [], array => [1,2,3,4]
var array = [1,2,3];
array.splice(0, 1); // => [1], array => [2,3]
var array = [1,2,3];
array.unshift(0); // => 4, array => [0,1,2,3]

// - accessor
[1,2,3].concat([4,5,6]); // => [1,2,3,4,5,6]
console.assert([1,2,3].join(',') == '1,2,3');
[1,2,3].slice(0, 2); // => [1,2]
console.assert([1,2,1].indexOf(1) == 0);
console.assert([1,2,1].indexOf(0) == -1);
console.assert([1,2,1].lastIndexOf(1) == 2);
console.assert([1,2,1].lastIndexOf(0) == -1);

// - iteration
[1,2,3].filter(function(e, i, a) { return e > 1; }); // => [2,3]
[1,2,3].every(function(e, i, a) { return e > 0; }); // => true
[1,2,3].map(function(e, i, a) { return e + 1; }); // => [2,3,4]
[1,2,3].some(function(e, i, a) { return e > 2; }); // => true
[1,2,3].reduce(function(a, b) { return a + b; }, 0); // => 6
[1,2,3].reduceRight(function(a, b) { return a + b; }, 0); // => 6
