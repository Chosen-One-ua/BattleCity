#ifndef MAPOBJECTTANK_H
#define MAPOBJECTTANK_H

#include "MapObject.h"

class MapObjectTank : public MapObject
{
	Q_OBJECT
		Q_PROPERTY(bool spacePressed READ getSpacePressed WRITE spacePressed)

public:
	explicit MapObjectTank(QObject* parent);

	virtual int			getCountBullets() const { return countBullets_; }
	virtual TypeTank	getTypeTank() const { return type_; }
	int					getSpacePressed() { return 0; }

	virtual void setCountBullets(int countBullets) { countBullets_ = countBullets; }
	virtual void setTypeTank(TypeTank type) { type_ = type; }
	virtual void setHealth(int health);

	void    spacePressed(bool);

public slots :
	void turnUser();
	void turnEnemies(int turn);
	void bulletDestroyed();

protected:
	int countBullets_ {};
	TypeTank type_;
};

#endif // MAPOBJECTTANK_H
