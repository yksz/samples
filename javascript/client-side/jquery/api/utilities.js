$.contains(document.documentElement, document.body); // => true
$.extend({a:1, b:2}, {b:3, c:4}); // => {a:1, b:3, c:4}
$.globalEval('var newVar = true;');
$.grep([1,2,3], function(e, i) { return e > 1 }); // => [2,3]
$.inArray('b', ['a',1,'b',2,'c',3]); // => 2
$.isArray([]); // => true
$.isEmptyObject({}); // => true
$.isFunction(function() {}); // => true
$.isNumeric('1'); // => true
$.isPlainObject({}); // => true
$.isWindow(window); // => true
$.isXMLDoc(document.body); // => false
$.makeArray(document.getElementsByTagName('div'));
$.map({a:1, b:2, c:3}, function(val, key) { return val }); // => [1,2,3]
$.merge([1,2,3], [4,5,6]); // => [1,2,3,4,5,6]
$.noop(); // an empty function
$.now(); // (new Date).getTime();
var html = $.parseHTML('<div></div>');
var json = $.parseJSON('{"name": "John"}');
var xml  = $.parseXML('<rss version="2.0"><channel></channel></rss>');
var func = $.proxy(function() { return this.id }, {id:1});
console.assert(func() == 1);
$.support; // browser information
$.trim(' abc  '); // => 'abc'
$.type(/test/); // => 'regexp'
$.unique($('div').get());
