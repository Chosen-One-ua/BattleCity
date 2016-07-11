#include "FactoryObstacles.h"
#include "MapObjectObstacle.h"
#include "BehaviorObstacle.h"
#include "GameController.h"

FactoryObstacles::FactoryObstacles(QObject* parent, GameController* controller)
	: Factory(parent, controller)
{}

MapObjectObstacle* FactoryObstacles::createMapObject(QPoint site, MapObject::TypeObstacle type)
{
	MapObjectObstacle* obstacle {new MapObjectObstacle(Map::getMap())};

	QPoint position {site.x() * Map::WidthSite, site.y() * Map::HeightSite};
	int layer {1};
	MapObject::Direction direction {MapObject::UP};
    QPair<int, int> size {2,2};
	QString imageSource {};
	bool moving {false};
	MapObject::Team team {MapObject::NEUTRALS};
	int health {4};
	int power {};
    int shield {1};
	Behavior* behavior {new BehaviorObstacle(obstacle)};
	

	switch (type) {
		case MapObject::EAGLE:
			imageSource = "qrc:/images/Eagle.png";
			size.first = size.second = 4;
			health = 1;
			break;

		case MapObject::BRICK:
            imageSource = "qrc:/images/Brick.png";
			health = 1;
			power = 1;
			break;

		case MapObject::STEEL:
            imageSource = "qrc:/images/Steel.png";
            health = 1;
			power = 1;
			shield = 3;
			break;

		case MapObject::WATER:
            imageSource = "qrc:/images/Water.png";
			health = 1;
			shield = 10;
			break;

		default:
			break;
	}

	obstacle->setPosition(position);
	obstacle->setLayer(layer);
	obstacle->setDirection(direction);
	obstacle->setSize(size);
	obstacle->setImageSource(imageSource);
	obstacle->setMoving(moving);
	obstacle->setTeam(team);
	obstacle->setHealth(health);
	obstacle->setPower(power);
	obstacle->setShield(shield);
	obstacle->setBehavior(behavior);
	obstacle->setTypeObstacle(type);

	return obstacle;
}
