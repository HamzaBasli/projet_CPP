import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6
Rectangle
    {
        property double oldLat : 25.6585
        property double oldLng : 100.3658
        Plugin {
        id : mapPlugin
        name : "osm"
    }
    Map
    {
        id : mapView
        anchors.fill: parent
        plugin : mapPlugin
        center:  QtPositioning.coordinate(oldLat , oldLng);
        zoomLevel: 6
    }
    function setCenter(Lat , Lng)
    {
        mapView.pan(oldLat - Lat , oldLng - Lng)
        oldlat = Lat
        oldLng = Lng
}
}
