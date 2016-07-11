import QtQuick 2.7

Item {
    x: modelData.positionX
    y: modelData.positionY
    width: modelData.width * 8
    height: modelData.height * 8
    focus: true

    Image {
        rotation: modelData.direction * 90
        source: modelData.imageSource
    }

    //TODO change int to enum
    Keys.onPressed: {
        if (event.key === Qt.Key_Right) {
            modelData.direction = "RIGHT"
            modelData.moving = true
            event.accepted = true
        } else if (event.key === Qt.Key_Down) {
            modelData.direction = "DOWN"
            modelData.moving = true
            event.accepted = true
        } else if (event.key === Qt.Key_Left) {
            modelData.direction = "LEFT"
            modelData.moving = true
            event.accepted = true
        } else if (event.key === Qt.Key_Up) {
            modelData.direction = "UP"
            modelData.moving = true
            event.accepted = true
        } else if (event.key === Qt.Key_Space) {
            modelData.spacePressed = true
            event.accepted = true
        }
    }

    Keys.onReleased: {
        if (event.key === Qt.Key_Right || event.key === Qt.Key_Down
                || event.key === Qt.Key_Left || event.key === Qt.Key_Up) {
            modelData.moving = false
            event.accepted = true
        }
        //modelData.spacePressed = false
        event.accepted = true
    }
}
