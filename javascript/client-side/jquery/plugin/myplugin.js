(function($) {

  $.fn.myplugin = function(options) {
    var settings = $.extend($.fn.myplugin.defaults, options);

    this.each(function() {
      $(this).mouseover(function() {
        $(this).animate({paddingLeft: settings.padding});
      }).mouseout(function() {
        $(this).animate({paddingLeft: '0'});
      });
    });

    return this;
  }

  $.fn.myplugin.defaults = {
    padding: '20px'
  };

})(jQuery);
