#include "MapObject.h"
#include "Map.h" 
#include "Behavior.h"

MapObject::MapObject(QObject* parent) : QObject(parent)
{}

int MapObject::getWidth() const
{
	return size_.first;
}

int MapObject::getHeight() const
{
	return size_.second;
}

void MapObject::setPosition(QPoint position)
{
	position_ = position;
	emit positionChanged();
}

void MapObject::setPositionX(int positionX)
{
	position_.rx() = positionX;
	emit positionChanged();
}

void MapObject::setPositionY(int positionY)
{
	position_.ry() = positionY;
	emit positionChanged();
}

void MapObject::setDirection(Direction direction)
{
	if (direction_ != direction) {
		direction_ = direction;
		position_.rx() = (position_.x() + Map::WidthSite / 2) / Map::WidthSite * Map::WidthSite;
		position_.ry() = (position_.y() + Map::HeightSite / 2) / Map::HeightSite * Map::HeightSite;
		emit directionChanged();
		emit positionChanged();
		Map::getMap()->updateMapObject(this);
	}
}

void MapObject::setImageSource(const QString& imageSource)
{
	imageSource_ = imageSource;
	emit imageSourceChanged();
}

void MapObject::setBehavior(Behavior* behavior)
{
	if (behavior_) {
		delete behavior_;
	}
	behavior_ = behavior;
}

MapObject::~MapObject()
{
	if (behavior_) {
		delete behavior_;
	}
}