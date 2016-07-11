#ifndef MAPSITE_H
#define MAPSITE_H

#include <QVector>

#include "Map.h"

class MapSite : public QObject
{
	Q_OBJECT

public:
	explicit MapSite(QObject*);
	MapObject* getMapObject(int layer) const;
	void setMapObject(MapObject* mapObject, int layer);

protected:
    QVector<MapObject*> site_;
};

#endif // MAPSITE_H
