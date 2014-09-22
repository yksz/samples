(function($) {

  $.fn.myplugin = function(options) {
    var elements = this;
    var settings = $.extend($.fn.myplugin.defaults, options);

    elements.each(function() {
      var element = $(this);
      element.mouseover(function() {
        element.animate({paddingLeft: settings.padding});
      }).mouseout(function() {
        element.animate({paddingLeft: '0'});
      });
    });

    return this;
  }

  $.fn.myplugin.defaults = {
    padding: '20px'
  };

})(jQuery);
