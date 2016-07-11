#include "MapObjectBullet.h"
#include "Behavior.h"
#include "Map.h"

MapObjectBullet::MapObjectBullet(QObject* parent) : MapObject(parent)
{}

void MapObjectBullet::turnBullet()
{
	behavior_->turn();
}

void MapObjectBullet::setHealth(int health)
{
	if (health > 0) {
		health_ = health;
	}
	else {
		Map::getMap()->destroyBullet(this);
	}
}

MapObjectBullet::~MapObjectBullet()
{
	emit bulletDestroyed();
}