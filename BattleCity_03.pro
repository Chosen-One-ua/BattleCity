include(deployment.pri)
TEMPLATE = app
QT += qml quick gui
CONFIG += c++11
TARGET = BattleCity_Sherstiuk_Andrii
HEADERS += \
    cpp/GameController.h \
    cpp/Map.h \
    cpp/MapSite.h \
    cpp/MapObject.h \
    cpp/MapObjectBullet.h \
    cpp/MapObjectObstacle.h \
    cpp/MapObjectTank.h \
    cpp/Factory.h \
    cpp/FactoryBullets.h \
    cpp/FactoryObstacles.h \
    cpp/FactoryTanks.h \
    cpp/Behavior.h \
    cpp/BehaviorBullet.h \
    cpp/BehaviorObstacle.h \
    cpp/BehaviorTank.h
SOURCES += \
    cpp/main.cpp \
    cpp/GameController.cpp \
    cpp/Map.cpp \
    cpp/MapSite.cpp \
    cpp/MapObject.cpp \
    cpp/MapObjectBullet.cpp \
    cpp/MapObjectObstacle.cpp \
    cpp/MapObjectTank.cpp \
    cpp/Factory.cpp \
    cpp/FactoryBullets.cpp \
    cpp/FactoryObstacles.cpp \
    cpp/FactoryTanks.cpp \
    cpp/Behavior.cpp \
    cpp/BehaviorBullet.cpp \
    cpp/BehaviorObstacle.cpp \
    cpp/BehaviorTank.cpp
RESOURCES += qml.qrc

DISTFILES +=
