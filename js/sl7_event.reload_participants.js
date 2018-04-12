(function ($, Drupal, window, document, undefined) {
  $(document).ready(function () {
    $('a.flag-link-toggle').bind('click', function() {
      setTimeout(function() {location.reload()}, 1000);
    });
  });
})(jQuery, Drupal, this, this.document);