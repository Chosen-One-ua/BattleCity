#ifndef MAP_H
#define MAP_H

#include <QQmlListProperty>

#include "MapObject.h"

class MapSite;
class MapObject;
class MapObjectTank;
class MapObjectBullet;
class MapObjectObstacle;
class FactoryTanks;
class FactoryBullets;
class FactoryObstacles;

class Map : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QQmlListProperty<MapObjectTank> userTanks READ getUserTanks NOTIFY userTanksChanged)
	Q_PROPERTY(QQmlListProperty<MapObjectTank> enemyTanks READ getEnemyTanks NOTIFY enemyTanksChanged)
	Q_PROPERTY(QQmlListProperty<MapObjectBullet> bullets READ getBullets NOTIFY bulletsChanged)
	Q_PROPERTY(QQmlListProperty<MapObjectObstacle> obstacles READ getObstacles NOTIFY obstaclesChanged)

public:
    static void initializationMap(QObject* gameController)
	{
		mapInstance_ = new Map(gameController);
	}
	static	Map* getMap()
	{
		if (!mapInstance_) {
			mapInstance_ = new Map();
		}
		return mapInstance_;
	}
	static const int LayersSite {4};
	static const int WidthMap {52};     //in map sites
	static const int HeightMap {52};
	static const int WidthSite {8};     //in px
	static const int HeightSite {8};

	QQmlListProperty<MapObjectTank>      getUserTanks();
	QQmlListProperty<MapObjectTank>      getEnemyTanks();
	QQmlListProperty<MapObjectBullet>    getBullets();
	QQmlListProperty<MapObjectObstacle>  getObstacles();

	MapObject* getMapObjectAt(QPoint site, int layer) const;
	void setMapObjectAt(MapObject*, QPoint site, int layer);

	void generateScenario();
	void clearMap();
	void clearRespawnPoint();

	bool tryBornUser();
	bool tryBornEnemy(MapObject::TypeTank);

	void createTank(QPoint, MapObject::TypeTank);
	void createBullet(QPoint, MapObject::TypeBullet, MapObjectTank*);
	void createObstacle(QPoint, MapObject::TypeObstacle);

	void bindObject(MapObject*);

	void destroyTank(MapObjectTank*);
	void destroyBullet(MapObjectBullet*);
	void destroyObstacle(MapObjectObstacle*);

	bool isEmptyPlace(QPoint, int);
	bool isEmptyEnemyBornPlace(int);
	bool isEmptyUserBornPlace(int);

	void updateMapObject(MapObject*);
	void objectEntersSite(MapObject*);
	void objectLeavesSite(MapObject*);

signals:
	void userTanksChanged(QQmlListProperty<MapObjectTank>);
	void enemyTanksChanged(QQmlListProperty<MapObjectTank>);
	void bulletsChanged(QQmlListProperty<MapObjectBullet>);
	void obstaclesChanged(QQmlListProperty<MapObjectObstacle>);

	void userDie();
	void enemyDie();

protected:
	static Map* mapInstance_;

	Map(QObject* = 0);
	Map(Map&);
	Map& operator = (Map&);

	MapSite*			 map_[WidthMap][HeightMap] {};

	QList<MapObjectTank*>      userTanks_;
	QList<MapObjectTank*>      enemyTanks_;
	QList<MapObjectBullet*>    bullets_;
	QList<MapObjectObstacle*>  obstacles_;

	FactoryTanks*     tanksFactory_;
	FactoryBullets*   bulletsFactory_;
	FactoryObstacles* obstaclesFactory_;
};

#endif // MAP_H
