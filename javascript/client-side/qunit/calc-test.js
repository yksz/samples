module('calc', {
  setup: function() {
  },
  teardown: function() {
  }
});
test('add test', function() {
  equal(3, add(1, 2), 'add(1, 2) => 3');
});
test('sub test', function() {
  equal(-1, sub(1, 2), 'sub(1, 2) => -1');
});
