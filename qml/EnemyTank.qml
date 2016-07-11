import QtQuick 2.7

Item {
    x: modelData.positionX
    y: modelData.positionY
    width: modelData.width * 8
    height: modelData.height * 8
        focus: false

    Image {
        rotation: modelData.direction * 90
        source: modelData.imageSource
    }
}
