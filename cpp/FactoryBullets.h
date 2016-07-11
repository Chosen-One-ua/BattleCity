#ifndef FACTORYBULLETS_H
#define FACTORYBULLETS_H

#include "Factory.h"

class FactoryBullets : public Factory
{
    Q_OBJECT

public:
    explicit FactoryBullets(QObject*, GameController*);
    MapObjectBullet* createMapObject(MapObject*,
                               QPoint,
                               MapObject::Direction,
                               MapObject::Team,
                               MapObject::TypeBullet);
};

#endif // FACTORYBULLETS_H
