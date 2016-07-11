#include "Behavior.h"

Behavior::Behavior(MapObject* parent) : QObject(parent)
{
	mapObject_ = parent;
}


void Behavior::hit(MapObject* target)
{
    if (target && mapObject_) {
        int hitTarget {mapObject_->getPower() - target->getShield()};
		int hitSelf {target->getPower() - mapObject_->getShield()};
		if (mapObject_->getTeam() != target->getTeam()) {
			if (hitTarget > 0) {
				target->setHealth(target->getHealth() - hitTarget);
			}
			if (hitSelf > 0) {
				if (mapObject_->getHealth() <= hitSelf) {
					mapObject_->setHealth(mapObject_->getHealth() - hitSelf);
					mapObject_ = nullptr;
                    return;
				}
				mapObject_->setHealth(mapObject_->getHealth() - hitSelf);
			}
		}
		if (target == mapObject_) {
			mapObject_->setHealth(mapObject_->getHealth() - 1);
		}
	}
}

Behavior::~Behavior()
{
	mapObject_ = nullptr;
}
