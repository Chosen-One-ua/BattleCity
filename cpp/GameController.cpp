#include <QQmlEngine>
#include <QQmlContext>
#include <QTimer>
#include <QTime>

#include "GameController.h"
#include "Map.h"
#include "MapObjectTank.h"
#include "MapObjectBullet.h"
#include "MapObjectObstacle.h"


GameController::GameController(QObject* parent, QQmlEngine* engine) : QObject(parent), engine_(engine)
{
	qmlRegisterType<MapObjectTank>();
	qmlRegisterType<MapObjectBullet>();
	qmlRegisterType<MapObjectObstacle>();

	Map::initializationMap(this);
	map_ = Map::getMap();
    connect(map_, &Map::userDie, this, &GameController::userDie);
    connect(map_, &Map::enemyDie, this, &GameController::enemyDie);

	engine->rootContext()->setContextProperty("map", map_);
	map_->generateScenario();


	timer_ = new QTimer(this);
	timer_->start(int(1000 / FramesPerSecond_));
	connect(timer_, &QTimer::timeout, this, &GameController::turnFrame);

	QTime midnight(0, 0, 0);
	qsrand(midnight.secsTo(QTime::currentTime()));
}

//void GameController::clearMap()
//{
//	if (map_) {
//		delete map_;
//	}
//	map_ = new Map(this);
//	connect(map, &Map::clearMap, this, &Controller::clearMap);
//	engine_->rootContext()->setContextProperty("map", map_);
//	map_->generateScenario();
//}

void GameController::turnFrame()
{
	++turn_;
	//TODO turnExplosions
	if (usersOnMap_ < 1) {
		if (map_->tryBornUser()) {
			++usersOnMap_;
		}
	}
    if (turn_ % 3200 && enemies_) {
		if (turn_ % 5) {
			if (map_->tryBornEnemy(MapObject::NORMAL_TANK)) {
				++enemiesOnMap_;
			}

		}
		else {
			if (map_->tryBornEnemy(MapObject::FAST_TANK)) {
				++enemiesOnMap_;
			}
		}
	}
	if ((turn_ % 4) < 3) {
		emit turnUser();
	}
	emit turnBullet();
	emit turnEnemies(turn_);
}


void GameController::userDie()
{
	--lifes_;
	--usersOnMap_;
	if (!lifes_) {
		exit(0);
	}
}

void GameController::enemyDie()
{
	--enemies_;
	--enemiesOnMap_;
	if (!(enemies_ + enemiesOnMap_)) {
		exit(0);
	}
}
