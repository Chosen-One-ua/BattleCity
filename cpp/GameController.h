#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QQmlEngine>
#include <QTimer>

class Map;

class GameController : public QObject
{
	Q_OBJECT
public:
	explicit GameController(QObject*, QQmlEngine*);

signals:
	void turnUser();
	void turnBullet();
	void turnEnemies(int);

public slots:
	//void clearMap();
	void turnFrame();
	void userDie();
	void enemyDie();

protected:
	QQmlEngine* engine_ {};
	Map* map_ {};
	QTimer* timer_ {};
	const int FramesPerSecond_ {64};
	unsigned int turn_ {};
	int lifes_ {3};
	int enemies_ {20};
	int enemiesOnMap_ {};
	int usersOnMap_ {};
};

#endif // CONTROLLER_H
