#ifndef BEHAVIOROBSTACLE_H
#define BEHAVIOROBSTACLE_H

#include "Behavior.h"

class BehaviorObstacle : public Behavior
{
	Q_OBJECT

public:
	BehaviorObstacle(MapObject*);

	virtual void turn();
};

#endif // BEHAVIOROBSTACLE_H
