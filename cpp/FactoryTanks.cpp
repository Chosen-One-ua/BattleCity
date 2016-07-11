#include "FactoryTanks.h"
#include "MapObjectTank.h"
#include "BehaviorTank.h"
#include "GameController.h"

FactoryTanks::FactoryTanks(QObject* parent, GameController* controller)
	: Factory(parent, controller)
{}

MapObjectTank* FactoryTanks::createMapObject(QPoint site, MapObject::TypeTank type)
{
	MapObjectTank* tank {new MapObjectTank(Map::getMap())};

	QPoint position {site.x() * Map::WidthSite, site.y() * Map::HeightSite};
	int layer {1};
	MapObject::Direction direction {MapObject::DOWN};
	QPair<int, int> size {4,4};
	QString imageSource {};
	bool moving {true};
	MapObject::Team team {MapObject::ENEMIES};
	int health {1};
	int power {1};
	int shield {1};
	Behavior* behavior {new BehaviorTank(tank)};
	int countBullets {1};

	switch (type) {
		case MapObject::USER_TANK:
			direction = MapObject::UP;
			imageSource = "qrc:/images/YellowNormalTank.png";
			moving = false;
			team = MapObject::USERS;
			break;

		case MapObject::NORMAL_TANK:
			imageSource = "qrc:/images/GrayNormalTank.png";
			break;

		case MapObject::FAST_TANK:
			imageSource = "qrc:/images/GrayFastTank.png";
			break;

		default:
			break;
	}

	tank->setPosition(position);
	tank->setLayer(layer);
	tank->setDirection(direction);
	tank->setSize(size);
	tank->setImageSource(imageSource);
	tank->setMoving(moving);
	tank->setTeam(team);
	tank->setHealth(health);
	tank->setPower(power);
	tank->setShield(shield);
	tank->setBehavior(behavior);
	tank->setCountBullets(countBullets);
	tank->setTypeTank(type);

	if (team == MapObject::USERS) {
		connect(gameController_, &GameController::turnUser, tank, &MapObjectTank::turnUser);
	}
	else {
		connect(gameController_, &GameController::turnEnemies, tank, &MapObjectTank::turnEnemies);
	}
	return tank;
}
