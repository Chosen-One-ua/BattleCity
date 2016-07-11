#ifndef MAPOBJECTBULLET_H
#define MAPOBJECTBULLET_H

#include "MapObject.h"

class MapObjectBullet : public MapObject
{
    Q_OBJECT

public:
	explicit MapObjectBullet(QObject*);

	virtual TypeBullet getType() const { return type_; }

	virtual void setType(TypeBullet type) { type_ = type; }
	virtual void setHealth(int health);

    ~MapObjectBullet();

signals:
    void bulletDestroyed();

public slots:
    void turnBullet();

protected:
	TypeBullet type_;
};

#endif // MAPOBJECTBULLET_H
