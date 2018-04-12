(function ($) {
  Drupal.behaviors.sl7_event = {
    attach: function (context, settings) {
      $('.geofield-ymap', context).once().bind('yandexMapInit', function (event, map) {

        var eventLabel = Drupal.settings.sl7_event.eventLabel;
        var extraAddress = Drupal.settings.sl7_event.extraAddress;
        var objects = map.geoObjects;

        objects.each(function(i) {
          i.properties.set({
            balloonContentHeader: eventLabel,
            openEmptyBalloon: true,
            balloonPanelMaxMapArea: 0
          });

          ymaps.geocode(i.geometry.getCoordinates(), {
            results: 1
          }).then(function (res) {
            var firstGeoObject = res.geoObjects.get(0);
            if (extraAddress) {
              i.properties.set({
                balloonContentBody: firstGeoObject.properties.get('text')+'<br />'+extraAddress
              });
            }
            else {
              i.properties.set({
                balloonContentBody: firstGeoObject.properties.get('text')
              });
            }
          });

          i.balloon.open();
        });

        Drupal.geofieldYmap.autoCentering(map);
        Drupal.geofieldYmap.autoZooming(map);
      });
    }
  };
})(jQuery);