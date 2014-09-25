function add(a, b) {
  return a + b;
}

console.assert(add()        != 3); // => NaN
console.assert(add(1)       != 3); // => NaN
console.assert(add(1, 2)    == 3);
console.assert(add(1, 2, 3) == 3);
