#include "MapObjectBullet.h"
#include "BehaviorBullet.h"
#include "Map.h"

BehaviorBullet::BehaviorBullet(MapObject* parent) : Behavior(parent)
{
	//bullet_ = dynamic_cast<MapObjectBullet*>(mapObject);
}

void BehaviorBullet::turn()
{
	switch (dynamic_cast<MapObjectBullet*>(mapObject_)->getType()) {
		case MapObject::SLOW_BULLET:
			move(2);
			break;

		case MapObject::FAST_BULLET:
			move(4);
			break;

		default:
			break;
	}

}

void BehaviorBullet::move(int shift)
{
	if (mapObject_) {
		switch (mapObject_->getDirection()) {
			case MapObject::RIGHT:
				moveRight(shift);
				break;

			case MapObject::DOWN:
				moveDown(shift);
				break;

			case MapObject::LEFT:
				moveLeft(shift);
				break;

			case MapObject::UP:
				moveUp(shift);
				break;

			default:
				break;
		}
	}
}

void BehaviorBullet::moveRight(int shift)
{
	if (mapObject_) {
		int x {mapObject_->getPositionX()};
		int y {mapObject_->getPositionY()};
		int dx {Map::WidthSite - x % Map::WidthSite};

		if (mapObject_->getPositionX() < (Map::WidthMap - 1)* Map::WidthSite) {
			if (!dx) {
				Map::getMap()->updateMapObject(mapObject_);
			}
			if (dx > shift) {
				mapObject_->setPositionX(x + shift);
			}
			else {
				mapObject_->setPositionX(x + dx);
				Map::getMap()->setMapObjectAt(nullptr, QPoint(x / Map::WidthSite - 1, y / Map::HeightSite), mapObject_->getLayer());

				MapObject* forwardMapObject {};

				forwardMapObject = Map::getMap()->getMapObjectAt(
					QPoint(x / Map::WidthSite, y / Map::HeightSite - 1), mapObject_->getLayer());
				if (forwardMapObject && forwardMapObject != mapObject_) {
					hit(forwardMapObject);
					return;
				}
				forwardMapObject = Map::getMap()->getMapObjectAt(
					QPoint(x / Map::WidthSite, y / Map::HeightSite), mapObject_->getLayer());
				if (forwardMapObject && forwardMapObject != mapObject_) {
					hit(forwardMapObject);
					return;
				}
				Map::getMap()->objectEntersSite(mapObject_);
				forwardMapObject = Map::getMap()->getMapObjectAt(
					QPoint(x / Map::WidthSite, y / Map::HeightSite - 1), mapObject_->getLayer() - 1);
				if (forwardMapObject) {
					hit(forwardMapObject);
					return;
				}
				forwardMapObject = Map::getMap()->getMapObjectAt(
					QPoint(x / Map::WidthSite, y / Map::HeightSite), mapObject_->getLayer() - 1);
				if (forwardMapObject) {
					hit(forwardMapObject);
					return;
				}
				/*if (mapObject_->getPositionX() < Map::WidthMap * Map::WidthSite) {
					Map::getMap()->objectEntersSite(mapObject_);
				}*/
				if (shift - dx) {
					move(shift - dx);
				}
			}
		}
		else {
			hit(mapObject_);
		}
	}
}

void BehaviorBullet::moveDown(int shift)
{
	if (mapObject_) {
		int x {mapObject_->getPositionX()};
		int y {mapObject_->getPositionY()};
		int dy {Map::HeightSite - y % Map::HeightSite};

		if (mapObject_->getPositionY() < (Map::HeightMap - 1)* Map::HeightSite) {

			if (dy > shift) {
				mapObject_->setPositionY(y + shift);
			}
			else {
				mapObject_->setPositionY(y + dy);

				Map::getMap()->setMapObjectAt(nullptr, QPoint(x / Map::WidthSite, y / Map::HeightSite - 1), mapObject_->getLayer());

				if (mapObject_->getPositionY() < (Map::HeightMap - 1)* Map::HeightSite) {
					MapObject* forwardMapObject {};
					forwardMapObject = Map::getMap()->getMapObjectAt(
						QPoint(x / Map::WidthSite - 1, y / Map::HeightSite), mapObject_->getLayer());
					if (forwardMapObject && forwardMapObject != mapObject_) {
						hit(forwardMapObject);
						return;
					}
					forwardMapObject = Map::getMap()->getMapObjectAt(
						QPoint(x / Map::WidthSite, y / Map::HeightSite), mapObject_->getLayer());
					if (forwardMapObject && forwardMapObject != mapObject_) {
						hit(forwardMapObject);
						return;
					}
					Map::getMap()->objectEntersSite(mapObject_);

					forwardMapObject = Map::getMap()->getMapObjectAt(
						QPoint(x / Map::WidthSite - 1, y / Map::HeightSite), mapObject_->getLayer() - 1);
					if (forwardMapObject) {
						hit(forwardMapObject);
						return;
					}
					forwardMapObject = Map::getMap()->getMapObjectAt(
						QPoint(x / Map::WidthSite, y / Map::HeightSite), mapObject_->getLayer() - 1);
					if (forwardMapObject) {
						hit(forwardMapObject);
						return;
					}
				}
				else {
					hit(mapObject_);
				}
				if (shift - dy) {
					move(shift - dy);
				}
			}
		}
		else {
			hit(mapObject_);
		}
	}
}
void BehaviorBullet::moveLeft(int shift)
{
	if (mapObject_) {
		int x {mapObject_->getPositionX()};
		int y {mapObject_->getPositionY()};
		int dx {x % Map::WidthSite + 1};

		if (mapObject_->getPositionX() >= Map::WidthSite) {
			
			if (dx > shift) {
				mapObject_->setPositionX(x - shift);
			}
			else {
				mapObject_->setPositionX(x - dx);
				Map::getMap()->setMapObjectAt(nullptr, QPoint(x / Map::WidthSite + 1, y / Map::HeightSite), mapObject_->getLayer());
				if (mapObject_->getPositionX() > Map::WidthSite * 1) {
					MapObject* forwardMapObject {};
					forwardMapObject = Map::getMap()->getMapObjectAt(
						QPoint(x / Map::WidthSite, y / Map::HeightSite - 1), mapObject_->getLayer());
					if (forwardMapObject && forwardMapObject != mapObject_) {
						hit(forwardMapObject);
						return;
					}
					forwardMapObject = Map::getMap()->getMapObjectAt(
						QPoint(x / Map::WidthSite, y / Map::HeightSite), mapObject_->getLayer());
					if (forwardMapObject && forwardMapObject != mapObject_) {
						hit(forwardMapObject);
						return;
					}
					Map::getMap()->objectEntersSite(mapObject_);
					forwardMapObject = Map::getMap()->getMapObjectAt(
						QPoint(x / Map::WidthSite, y / Map::HeightSite - 1), mapObject_->getLayer() - 1);
					if (forwardMapObject) {
						hit(forwardMapObject);
						return;
					}
					forwardMapObject = Map::getMap()->getMapObjectAt(
						QPoint(x / Map::WidthSite, y / Map::HeightSite), mapObject_->getLayer() - 1);
					if (forwardMapObject) {
						hit(forwardMapObject);
						return;
					}
				}
				else {
					hit(mapObject_);
				}
				if (shift - dx) {
					move(shift - dx);
				}
			}
		}
		else {
			hit(mapObject_);
		}
	}
}

void BehaviorBullet::moveUp(int shift)
{
	if (mapObject_) {
		int x {mapObject_->getPositionX()};
		int y {mapObject_->getPositionY()};
		int dy {y % Map::HeightSite + 1};

		if (mapObject_->getPositionY() >= Map::WidthSite) {
			if (!dy) {
				Map::getMap()->updateMapObject(mapObject_);
			}
			if (dy > shift) {
				mapObject_->setPositionY(y - shift);
			}
			else {
				mapObject_->setPositionY(y - dy);
				Map::getMap()->setMapObjectAt(nullptr, QPoint(x / Map::WidthSite, y / Map::HeightSite + 1), mapObject_->getLayer());
				if (mapObject_->getPositionY() > Map::HeightSite * 1) {
					MapObject* forwardMapObject {};
					forwardMapObject = Map::getMap()->getMapObjectAt(
						QPoint(x / Map::WidthSite - 1, y / Map::HeightSite), mapObject_->getLayer());
					if (forwardMapObject && forwardMapObject != mapObject_) {
						hit(forwardMapObject);
						return;
					}
					forwardMapObject = Map::getMap()->getMapObjectAt(
						QPoint(x / Map::WidthSite, y / Map::HeightSite), mapObject_->getLayer());
					if (forwardMapObject && forwardMapObject != mapObject_) {
						hit(forwardMapObject);
						return;
					}
					Map::getMap()->objectEntersSite(mapObject_);
					forwardMapObject = Map::getMap()->getMapObjectAt(
						QPoint(x / Map::WidthSite - 1, y / Map::HeightSite), mapObject_->getLayer() - 1);
					if (forwardMapObject) {
						hit(forwardMapObject);
						return;
					}
					forwardMapObject = Map::getMap()->getMapObjectAt(
						QPoint(x / Map::WidthSite, y / Map::HeightSite), mapObject_->getLayer() - 1);
					if (forwardMapObject) {
						hit(forwardMapObject);
						return;
					}
				}
				else {
					hit(mapObject_);
				}
				if (shift - dy) {
					move(shift - dy);
				}
			}
		}
		else {
			hit(mapObject_);
		}
	}
}
