#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include "MapObject.h"

class Behavior : public QObject
{
	Q_OBJECT

public:
	explicit Behavior(MapObject*);
	virtual void turn() = 0;
	virtual void hit(MapObject* target);

	MapObject* mapObject_; //temporary public

	~Behavior();
protected:
	
};

#endif // BEHAVIOR_H