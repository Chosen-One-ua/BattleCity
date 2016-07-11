#include "MapSite.h"

MapSite::MapSite(QObject* parent) : QObject(parent){
    site_ = QVector<MapObject*> {Map::LayersSite};
}

MapObject* MapSite::getMapObject(int layer) const
{
    if (layer >= 0 && layer < Map::LayersSite && site_[layer]) {
		return site_[layer];
	}
	else {
		return nullptr;
	}
}

void MapSite::setMapObject(MapObject* mapObject, int layer)
{
	if (layer >= 0 && layer < Map::LayersSite) {
		site_[layer] = mapObject;
	}
}

