#include "MapSite.h"
#include "FactoryBullets.h"
#include "FactoryObstacles.h"
#include "FactoryTanks.h"
#include "GameController.h"

#include "MapObjectTank.h"
#include "MapObjectBullet.h"
#include "MapObjectObstacle.h"

Map* Map::mapInstance_ = nullptr;

Map::Map(QObject *parent) : QObject(parent)
{
	tanksFactory_ = new FactoryTanks(this, dynamic_cast<GameController*>(parent));
	bulletsFactory_ = new FactoryBullets(this, dynamic_cast<GameController*>(parent));
	obstaclesFactory_ = new FactoryObstacles(this, dynamic_cast<GameController*>(parent));

	for (int i {0}; i < 52; ++i) {
		for (int j {0}; j < 52; ++j) {
			map_[i][j] = new MapSite(this);
		}
	}

	//generateScenario();
}

QQmlListProperty<MapObjectTank> Map::getUserTanks()
{
	return QQmlListProperty<MapObjectTank>(this, userTanks_);
}

QQmlListProperty<MapObjectTank> Map::getEnemyTanks()
{
	return QQmlListProperty<MapObjectTank>(this, enemyTanks_);
}

QQmlListProperty<MapObjectBullet> Map::getBullets()
{
	return QQmlListProperty<MapObjectBullet>(this, bullets_);
}

QQmlListProperty<MapObjectObstacle> Map::getObstacles()
{
	return QQmlListProperty<MapObjectObstacle>(this, obstacles_);
}

MapObject * Map::getMapObjectAt(QPoint site, int layer) const
{
	return map_[site.x()][site.y()]->getMapObject(layer);
}

void Map::setMapObjectAt(MapObject* mapObject, QPoint site, int layer)
{
	map_[site.x()][site.y()]->setMapObject(mapObject, layer);
}

void Map::generateScenario()
{
	clearMap();
	createObstacle(QPoint(24, 48), MapObject::EAGLE);

	for (int i {10}; i < 40; i += 2) {
		createObstacle(QPoint(i, 30), MapObject::BRICK);
		createObstacle(QPoint(i, 20), MapObject::WATER);
		createObstacle(QPoint(i, 10), MapObject::STEEL);
	}
	clearRespawnPoint();
}
void Map::clearMap()
{
	//emit clearMap();
}

void Map::clearRespawnPoint()
{
	//TODO
}

bool Map::tryBornUser()
{
	if (qrand() % 2) {
		if (isEmptyUserBornPlace(1)) {
			createTank(QPoint(28, 48), MapObject::USER_TANK);
			return true;
		}
	}
	else if (isEmptyUserBornPlace(0)) {
		createTank(QPoint(20, 48), MapObject::USER_TANK);
		return true;
	}
	return false;
}

bool Map::tryBornEnemy(MapObject::TypeTank type)
{
	switch (qrand() % 3) {
		case 0:
			if (isEmptyEnemyBornPlace(0)) {
				createTank(QPoint(0, 0), type);
				return true;
			}
			break;

		case 1:
			if (isEmptyEnemyBornPlace(1)) {
				createTank(QPoint(24, 0), type);
				return true;
			}
			break;

		case 2:
			if (isEmptyEnemyBornPlace(2)) {
				createTank(QPoint(48, 0), type);
				return true;
			}
			break;

		default:
			break;
	}
	return false;
}

void Map::createTank(QPoint site, MapObject::TypeTank type)
{
	MapObjectTank* tank {tanksFactory_->createMapObject(site, type)};
	if (tank->getTeam() == MapObject::USERS) {
		userTanks_.append(tank);
		emit userTanksChanged(getUserTanks());
	}
	else {
		enemyTanks_.append(tank);
		emit enemyTanksChanged(getEnemyTanks());
	}
	bindObject(tank);
}

void Map::createBullet(QPoint site, MapObject::TypeBullet type, MapObjectTank* tank)
{
	MapObjectBullet* bullet {bulletsFactory_->createMapObject(tank, site, tank->getDirection(), 
															  tank->getTeam(), type)};
	bullets_.append(bullet);
	emit bulletsChanged(getBullets());
	bindObject(bullet);
}

void Map::createObstacle(QPoint site, MapObject::TypeObstacle type)
{
	MapObjectObstacle* obstacle {obstaclesFactory_->createMapObject(site, type)};
	obstacles_.append(obstacle);
	emit obstaclesChanged(getObstacles());
	bindObject(obstacle);
}

void Map::bindObject(MapObject* mapObject)
{
	int x {mapObject->getPositionX() / WidthSite};
	int y {mapObject->getPositionY() / HeightSite};

	int i {x};
	do {
		int  j {y};
		do {
			map_[i][j]->setMapObject(mapObject, mapObject->getLayer());
			++j;
		}
		while (j < y + mapObject->getHeight());
		++i;
	}
	while (i < x + mapObject->getWidth());
}

void Map::destroyTank(MapObjectTank* tank)
{
	if (tank) {
		updateMapObject(tank);
		int x {tank->getPositionX() / WidthSite};
		int y {tank->getPositionY() / HeightSite};
		switch (tank->getTeam()) {
			case MapObject::USERS:
				userTanks_.removeOne(tank);
				emit userTanksChanged(getUserTanks());
				emit userDie();
				exit(0);
				break;

			case MapObject::ENEMIES:
				enemyTanks_.removeOne(tank);
				emit enemyTanksChanged(getEnemyTanks());
				emit enemyDie();
				break;

			default:
				break;
		}
		for (int i {x}; i < x + tank->getWidth(); ++i) {
			for (int j {y}; j < y + tank->getHeight(); ++j) {
				map_[i][j]->setMapObject(nullptr, tank->getLayer());
			}
		}
		delete tank;
	}
}

void Map::destroyBullet(MapObjectBullet* bullet)
{
	if (bullet) {
		int x {bullet->getPositionX() / WidthSite};
		int y {bullet->getPositionY() / HeightSite};

		bullets_.removeOne(bullet);
		emit bulletsChanged(getBullets());
		map_[x][y]->setMapObject(nullptr, bullet->getLayer());

		delete bullet;
	}
}

void Map::destroyObstacle(MapObjectObstacle* obstacle)
{
	if (obstacle) {
		int x {obstacle->getPositionX() / WidthSite};
		int y {obstacle->getPositionY() / HeightSite};

		obstacles_.removeOne(obstacle);
		emit obstaclesChanged(getObstacles());
		for (int i {x}; i < x + obstacle->getWidth(); ++i) {
			for (int j {y}; j < y + obstacle->getHeight(); ++j) {
				map_[i][j]->setMapObject(nullptr, obstacle->getLayer());
			}
		}
		delete obstacle;
	}
}

bool Map::isEmptyPlace(QPoint site, int layer)
{
	if (map_[site.x()][site.y()]->getMapObject(layer)) {
		return false;
	}
	return true;
}

bool Map::isEmptyEnemyBornPlace(int number)
{
	if (number < 3 && number >= 0) {
		for (int i {}; i < 4; ++i) {
			for (int j {}; j < 4; ++j) {
				if (!isEmptyPlace(QPoint(number * 24 + i, j), 1)) {
					return false;
				}
			}
		}
		return true;
	}
	return false;
}

bool Map::isEmptyUserBornPlace(int number)
{
	if (number < 2 && number >= 0) {
		for (int i {}; i < 4; ++i) {
			for (int j {48}; j < 52; ++j) {
				if (!isEmptyPlace(QPoint(number * 12 + 18 + i, j), 1)) {
					return false;
				}
			}
		}
		return true;
	}
	return false;
}

void Map::objectEntersSite(MapObject* mapObject)
{
	int x {mapObject->getPositionX() / WidthSite};
	int y {mapObject->getPositionY() / HeightSite};
	int i {};
	switch (mapObject->getDirection()) {
		case MapObject::RIGHT:
			i = 0;
			do {
				(map_[x + mapObject->getWidth()][y + i])->setMapObject(mapObject, mapObject->getLayer());
			}
			while (++i < mapObject->getHeight());
			break;

		case MapObject::DOWN:
			i = 0;
			do {
				(map_[x + i][y + mapObject->getHeight()])->setMapObject(mapObject, mapObject->getLayer());
			}
			while (++i < mapObject->getWidth());
			break;

		case MapObject::LEFT:
			i = 0;
			do {
				(map_[x][y + i])->setMapObject(mapObject, mapObject->getLayer());
			}
			while (++i < mapObject->getHeight());
			break;

		case MapObject::UP:
			i = 0;
			do {
				(map_[x + i][y])->setMapObject(mapObject, mapObject->getLayer());
			}
			while (++i < mapObject->getWidth());
			break;

		default:
			break;
	}
}
void Map::objectLeavesSite(MapObject* mapObject)
{
	int x {mapObject->getPositionX() / WidthSite};
	int y {mapObject->getPositionY() / HeightSite};
	int i {};
	switch (mapObject->getDirection()) {
		case MapObject::RIGHT:
			i = 0;
			do {
				(map_[x - 1][y + i])->setMapObject(nullptr, mapObject->getLayer());
			}
			while (++i < mapObject->getHeight());
			break;

		case MapObject::DOWN:
			i = 0;
			do {
				(map_[x + i][y - 1])->setMapObject(nullptr, mapObject->getLayer());
			}
			while (++i < mapObject->getWidth());
			break;

		case MapObject::LEFT:
			i = 0;
			do {
				(map_[x + mapObject->getWidth()][y + i])->setMapObject(nullptr, mapObject->getLayer());
			}
			while (++i < mapObject->getHeight());
			break;

		case MapObject::UP:
			i = 0;
			do {
				(map_[x + i][y + mapObject->getHeight()])->setMapObject(nullptr, mapObject->getLayer());
			}
			while (++i < mapObject->getWidth());
			break;

		default:
			break;
	}
}

void Map::updateMapObject(MapObject* mapObject)
{
	int x {mapObject->getPositionX() / WidthSite};
	int y {mapObject->getPositionY() / HeightSite};
	int i {};
	if (x > 0) {
		i = 0;
		do {
			if ((map_[x - 1][y + i])->getMapObject(mapObject->getLayer()) == mapObject) {
				(map_[x - 1][y + i])->setMapObject(nullptr, mapObject->getLayer());
			}
		}
		while (++i < mapObject->getHeight());
	}
	if (x < WidthMap - mapObject->getWidth()) {
		i = 0;
		do {
			if (map_[x + mapObject->getWidth()][y + i]->getMapObject(mapObject->getLayer()) == mapObject) {
				(map_[x + mapObject->getWidth()][y + i])->setMapObject(nullptr, mapObject->getLayer());
			}
		}
		while (++i < mapObject->getHeight());
	}
	if (y > 0) {
		i = 0;
		do {
			if (map_[x + i][y - 1]->getMapObject(mapObject->getLayer()) == mapObject) {
				(map_[x + i][y - 1])->setMapObject(nullptr, mapObject->getLayer());
			}
		}
		while (++i < mapObject->getWidth());
	}
	if (y < HeightMap - mapObject->getHeight()) {
		i = 0;
		do {
			if (map_[x + i][y + mapObject->getHeight()]->getMapObject(mapObject->getLayer()) == mapObject) {
				(map_[x + i][y + mapObject->getHeight()])->setMapObject(nullptr, mapObject->getLayer());
			}
		}
		while (++i < mapObject->getWidth());
	}
}
