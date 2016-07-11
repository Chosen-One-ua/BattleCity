#ifndef MAPOBJECTOBSTACLE_H
#define MAPOBJECTOBSTACLE_H

#include "MapObject.h"

class MapObjectObstacle : public MapObject
{
	Q_OBJECT

public:
	explicit MapObjectObstacle(QObject*);

	virtual TypeObstacle getTypeObstacle() const { return type_; }

	virtual void setTypeObstacle(TypeObstacle type) { type_ = type; }
	virtual void setHealth(int health);

	~MapObjectObstacle();

signals:
	void gameOver(); //TODO

protected:
	TypeObstacle type_ {};  
};

#endif // MAPOBJECTOBSTACLE_H
