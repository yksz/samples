var project = project || {};

project.ModuleA = function(name) { // constructor
  var _name = '<' + name + '>'; // private field

  return {
    version: '0.1', // public field

    toString: function() { // public method
      return 'project.ModuleA [name=' + _name + ', version=' + this.version + ']';
    }
  };
};
