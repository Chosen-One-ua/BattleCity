#ifndef BEHAVIORTANK_H
#define BEHAVIORTANK_H

#include "Behavior.h"

class MapObjectTank;

class BehaviorTank : public Behavior
{
	Q_OBJECT

public:
	BehaviorTank(MapObject*);

	virtual void turn();
	virtual void move(int shift);
	virtual void moveRight(int shift);
	virtual void moveDown(int shift);
	virtual void moveLeft(int shift);
	virtual void moveUp(int shift);
	virtual void tankShot();

private:
	MapObjectTank* tank;
};

#endif // BEHAVIORTANK_H
