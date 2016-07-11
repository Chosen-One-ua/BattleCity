import QtQuick 2.7

Item {

    x: modelData.positionX
    y: modelData.positionY
    width: 6
    height: 8

    Image {
        rotation: modelData.direction * 90
        source: modelData.imageSource
    }


}
