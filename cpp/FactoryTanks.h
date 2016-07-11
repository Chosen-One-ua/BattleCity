#ifndef FACTORYTANKS_H
#define FACTORYTANKS_H

#include "Factory.h"

class FactoryTanks : public Factory
{
	Q_OBJECT

public:
	explicit FactoryTanks(QObject*, GameController*);
	MapObjectTank* createMapObject(QPoint, MapObject::TypeTank);
};

#endif // FACTORYTANKS_H
