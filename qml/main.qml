import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.1

ApplicationWindow {
    visible: true
    width: 416
    height: 416
    Rectangle {
        x: 0
        y: 0
        width: 416
        height: 416
        color: "#000"

        //Grid {
        //anchors.horizontalCenter: parent.horizontalCenter
        //anchors.verticalCenter: parent.verticalCenter
        //columns: 5
        //spacing: 0
        Repeater {
            model: map.userTanks
            UserTank {
            }
        }
        Repeater {
            model: map.enemyTanks
            EnemyTank {
            }
        }
        Repeater {
            model: map.bullets
            Bullet {
            }
        }
        Repeater {
            model: map.obstacles
            Obstacle {
            }
        }

        //}
    }
}
