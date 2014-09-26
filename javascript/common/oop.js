function Foo(name) {
  if (!(this instanceof Foo))
    throw new Error('Foo is a constructor');
  this.name = name;
}
Foo.prototype.getName = function() {
  return this.name
};

function Bar() {
  if (!(this instanceof Bar))
    throw new Error('Bar is a constructor');
  Foo.apply(this, arguments);
}
Bar.prototype = new Foo;

var foo = new Foo('foo');
var bar = new Bar('bar');
var hoge = Object.create(Foo.prototype, {name: {value: 'hoge'}});
console.log(foo.getName());
console.log(bar.getName());
console.log(hoge.getName());
