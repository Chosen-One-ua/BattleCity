#include "MapObjectTank.h"
#include "BehaviorTank.h"
#include "Map.h"

MapObjectTank::MapObjectTank(QObject* parent) :MapObject(parent)
{}

void MapObjectTank::setHealth(int health)
{
	if (health > 0) {
		health_ = health;
	}
	else {
		Map::getMap()->destroyTank(this);
	}
}

void MapObjectTank::spacePressed(bool key)
{
	if (key) {
		dynamic_cast<BehaviorTank*>(behavior_)->tankShot();
	}
}

void MapObjectTank::turnUser()
{
	behavior_->turn();
}

void MapObjectTank::turnEnemies(int turn)
{
	if (type_ == MapObject::FAST_TANK || turn % 2) {
		behavior_->turn();
	}
}

void MapObjectTank::bulletDestroyed()
{
	++countBullets_;
}