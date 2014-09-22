var project = project || {};

project.ModuleB = (function() {
  var __id = 0; // private static field

  return function(name) { // constructor
    var _id = __id++; // private field
    var _name = '<' + name + '>'; // private field

    return {
      version: '0.1', // public field

      toString: function() { // public method
        return 'project.ModuleB [id=' + _id + ', name=' + name + ', version=' + this.version + ']';
      }
    };
  };
})();
