#include "FactoryBullets.h"
#include "MapObjectBullet.h"
#include "MapObjectTank.h"
#include "BehaviorBullet.h"
#include "GameController.h"

FactoryBullets::FactoryBullets(QObject* parent, GameController* controller)
	: Factory(parent, controller)
{}

MapObjectBullet* FactoryBullets::createMapObject(MapObject* tank,
										   QPoint site,
										   MapObject::Direction direction,
										   MapObject::Team team,
										   MapObject::TypeBullet type)
{
	MapObjectBullet* bullet {new MapObjectBullet(Map::getMap())};


	QPoint position {site.x() * Map::WidthSite, site.y() * Map::HeightSite};
	int layer {2};
	QPair<int, int> size {0,0};
	QString imageSource {"qrc:/images/Bullet.png"};
	bool moving {true};
	int health {1};
	int power {2};
	int shield {};
	Behavior* behavior {new BehaviorBullet(bullet)};

	bullet->setPosition(position);
	bullet->setLayer(layer);
	bullet->setDirection(direction);
	bullet->setSize(size);
	bullet->setImageSource(imageSource);
	bullet->setMoving(moving);
	bullet->setTeam(team);
	bullet->setHealth(health);
	bullet->setPower(power);
	bullet->setShield(shield);
	bullet->setBehavior(behavior);
	bullet->setType(type);

	connect(gameController_, &GameController::turnBullet, bullet, &MapObjectBullet::turnBullet);
	connect(bullet, &MapObjectBullet::bulletDestroyed, dynamic_cast<MapObjectTank*>(tank), &MapObjectTank::bulletDestroyed);
	
	return bullet;
}
