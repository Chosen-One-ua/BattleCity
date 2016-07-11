#ifndef FACTORYOBSTACLES_H
#define FACTORYOBSTACLES_H

#include "factory.h"

class FactoryObstacles : public Factory
{
	Q_OBJECT

public:
	explicit FactoryObstacles(QObject*, GameController*);
	MapObjectObstacle* createMapObject(QPoint site, MapObject::TypeObstacle);
};

#endif // FACTORYOBSTACLES_H
