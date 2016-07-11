#ifndef BEHAVIORBULLET_H
#define BEHAVIORBULLET_H

#include "Behavior.h"

class MapObjectBullet;

class BehaviorBullet : public Behavior
{
    Q_OBJECT

public:
	explicit BehaviorBullet(MapObject*);

	virtual void turn();
	virtual void move(int shift);
	virtual void moveRight(int shift);
	virtual void moveDown(int shift);
	virtual void moveLeft(int shift);
	virtual void moveUp(int shift);

private:
	//MapObjectBullet* bullet_;
};

#endif // BEHAVIORBULLET_H
