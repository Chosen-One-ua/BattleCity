#include "BehaviorTank.h"
#include "MapObjectTank.h"
#include "Map.h"

BehaviorTank::BehaviorTank(MapObject* parent) : Behavior(parent)
{
	tank = (dynamic_cast<MapObjectTank*>(mapObject_));
}

void BehaviorTank::turn()
{
	if (tank->getTeam() != MapObject::USERS) {
		int poorAi {qrand() % 32};
		if (!poorAi) {
			tank->setDirection(MapObject::Direction(qrand() % 4 + 1));
		}
		if (!(qrand() % 128)) {
			tankShot();
		}

	}
	if (tank->getMoving()) {
		move(1);
	}
}

void BehaviorTank::move(int shift)
{
	switch (tank->getDirection()) {
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

void BehaviorTank::moveRight(int shift)
{
	int x {tank->getPositionX()};
	int y {tank->getPositionY()};
	if (x < (Map::WidthMap - tank->getWidth())* Map::WidthSite) {
		int dx {Map::WidthSite - x % Map::WidthSite};
		if (dx > shift) {
			if (x % Map::WidthSite) {
				tank->setPositionX(x + shift);
			}
			else {
				Map::getMap()->updateMapObject(mapObject_);
				MapObject* forwardMapObject {};
				bool canMove {true};
				for (int i {0}; i < tank->getHeight(); ++i) {
					forwardMapObject = Map::getMap()->getMapObjectAt(
						QPoint(x / Map::WidthSite + tank->getWidth(), y / Map::HeightSite + i), tank->getLayer());
					if (forwardMapObject) {
						if (!tank) {
							return;
						}
						canMove = false;
					}
				}
				if (canMove) {
					tank->setPositionX(x + shift);
					Map::getMap()->objectEntersSite(tank);
				}
			}
		}
		else {
			tank->setPositionX(x + dx);
			Map::getMap()->objectLeavesSite(tank);
			if (shift - dx) {
				moveRight(shift - dx);
			}
		}
	}
}

void BehaviorTank::moveDown(int shift)
{
	int x {tank->getPositionX()};
	int y {tank->getPositionY()};
	if (y < (Map::HeightMap - tank->getHeight())* Map::HeightSite) {
		int dy {Map::HeightSite - x % Map::HeightSite};
		if (dy > shift) {
			if (y % Map::HeightSite) {
				tank->setPositionY(y + shift);
			}
			else {
				Map::getMap()->updateMapObject(mapObject_);
				MapObject* forwardMapObject {};
				bool canMove {true};
				for (int i {0}; i < tank->getWidth(); ++i) {
					forwardMapObject = Map::getMap()->getMapObjectAt(
						QPoint(x / Map::WidthSite + i, y / Map::HeightSite + tank->getHeight()), tank->getLayer());
					if (forwardMapObject) {
						if (!tank) {
							return;
						}
						canMove = false;
					}
				}
				if (canMove) {
					tank->setPositionY(y + shift);
					Map::getMap()->objectEntersSite(tank);
				}
			}
		}
		else {
			tank->setPositionY(y + dy);
			Map::getMap()->objectLeavesSite(tank);
			if (shift - dy) {
				moveRight(shift - dy);
			}
		}
	}
}

void BehaviorTank::moveLeft(int shift)
{
	int x {tank->getPositionX()};
	int y {tank->getPositionY()};
	if (x > 0) {
		int dx {x % Map::WidthSite};
		if (dx) {
			if (dx > shift) {
				tank->setPositionX(x - shift);
			}
			else {
				tank->setPositionX(x - dx);
				Map::getMap()->objectLeavesSite(tank);
				if (shift - dx) {
					moveLeft(shift - dx);
				}
			}
		}
		else {
			Map::getMap()->updateMapObject(mapObject_);
			MapObject* forwardMapObject {};
			bool canMove {true};
			for (int i {0}; i < tank->getHeight(); ++i) {
				forwardMapObject = Map::getMap()->getMapObjectAt(
					QPoint(x / Map::WidthSite - 1, y / Map::HeightSite + i), tank->getLayer());
				if (forwardMapObject) {
					if (!tank) {
						return;
					}
					canMove = false;
				}
			}
			if (canMove) {
				tank->setPositionX(x - shift);
				Map::getMap()->objectEntersSite(tank);
			}
		}
	}
}

void BehaviorTank::moveUp(int shift)
{
	int x {tank->getPositionX()};
	int y {tank->getPositionY()};
	if (y > 0) {
		int dy {y % Map::HeightSite};
		if (dy) {
			if (dy > shift) {
				tank->setPositionY(y - shift);
			}
			else {
				tank->setPositionY(y - dy);
				Map::getMap()->objectLeavesSite(tank);
				if (shift - dy) {
					moveLeft(shift - dy);
				}
			}
		}
		else {
			Map::getMap()->updateMapObject(mapObject_);
			MapObject* forwardMapObject {};
			bool canMove {true};
			for (int i {0}; i < tank->getWidth(); ++i) {
				forwardMapObject = Map::getMap()->getMapObjectAt(
					QPoint(x / Map::WidthSite + i, y / Map::HeightSite - 1), tank->getLayer());
				if (forwardMapObject) {
					if (!tank) {
						return;
					}
					canMove = false;
				}
			}
			if (canMove) {
				tank->setPositionY(y - shift);
				Map::getMap()->objectEntersSite(tank);
			}
		}
	}
}

void BehaviorTank::tankShot()
{
	if (tank) {
		if (tank->getCountBullets()) {
			QPoint siteShot {};
			int x {tank->getPositionX() / Map::WidthSite};
			int y {tank->getPositionY() / Map::HeightSite};
			switch (tank->getDirection()) {
				case MapObject::RIGHT:
					siteShot.rx() = x + tank->getWidth();
					siteShot.ry() = y + tank->getHeight() / 2;
					break;

				case MapObject::DOWN:
					siteShot.rx() = x + tank->getWidth() / 2;
					siteShot.ry() = y + tank->getHeight();
					break;

				case MapObject::LEFT:
					siteShot.rx() = x;
					siteShot.ry() = y + tank->getHeight() / 2;
					break;

				case MapObject::UP:
					siteShot.rx() = x + tank->getWidth() / 2;
					siteShot.ry() = y;
					break;

				default:
					break;
			}
			if (siteShot.x() >= 0 && siteShot.x() < 52 && siteShot.y() >= 0 && siteShot.y() < 52) {
				Map::getMap()->createBullet(siteShot, MapObject::SLOW_BULLET, tank);
				tank->setCountBullets(tank->getCountBullets() - 1);

			}
		}
	}
}
