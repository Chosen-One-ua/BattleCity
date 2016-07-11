#include "MapObjectObstacle.h"
#include "Behavior.h"
#include "Map.h"
MapObjectObstacle::MapObjectObstacle(QObject* parent) : MapObject(parent)
{}

void MapObjectObstacle::setHealth(int health)
{
	if (health > 0) {
		health_ = health;
	}
	else {
		Map::getMap()->destroyObstacle(this);
	}
}

MapObjectObstacle::~MapObjectObstacle()
{
	if (type_ == EAGLE) {
		//emit gameOver();
		exit(0);
	}
}