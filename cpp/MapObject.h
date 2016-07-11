#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include <QObject>
#include <QPoint>

class Map;
class Behavior;

class MapObject : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int positionX READ getPositionX NOTIFY positionChanged)
	Q_PROPERTY(int positionY READ getPositionY NOTIFY positionChanged)
	Q_PROPERTY(int width READ getWidth)
	Q_PROPERTY(int height READ getHeight)
	Q_PROPERTY(QString imageSource READ getImageSource NOTIFY imageSourceChanged)
	Q_PROPERTY(Direction direction READ getDirection WRITE setDirection NOTIFY directionChanged)
	Q_PROPERTY(bool moving READ getMoving WRITE setMoving)

public:
	enum TypeTank { USER_TANK, NORMAL_TANK, FAST_TANK, BATTLE_TANK, HEAVY_TANK };
	Q_ENUM(TypeTank)
	enum TypeBullet { SLOW_BULLET, FAST_BULLET };
	Q_ENUM(TypeBullet)
	enum TypeObstacle { EAGLE, BRICK, STEEL, WATER };
	Q_ENUM(TypeObstacle)
	enum Direction { NONE, RIGHT, DOWN, LEFT, UP };
	Q_ENUM(Direction)
	enum Team { USERS, ENEMIES, NEUTRALS };
	Q_ENUM(Team)

	explicit MapObject(QObject*);

	virtual const QPoint&   getPosition() const { return position_; }
	virtual int				getPositionX() const { return position_.x(); }
	virtual int				getPositionY() const { return position_.y(); }
	virtual int				getLayer() const { return layer_; }
	virtual Direction		getDirection() const { return direction_; }
	virtual const QPair<int, int>& getSize() const { return size_; }
	virtual int				getWidth() const;
	virtual int				getHeight() const;
	virtual const QString&	getImageSource() const { return imageSource_; }
	virtual bool			getMoving() const { return moving_; }
	virtual Team			getTeam() const { return team_; }
	virtual int				getHealth() { return health_; }
	virtual int				getPower() const { return power_; }
	virtual int				getShield() const { return shield_; }

	virtual void setPosition(QPoint);
	virtual void setPositionX(int positionX);
	virtual void setPositionY(int positionY);
	virtual void setLayer(int layer) { layer_ = layer; }
	virtual void setDirection(Direction);
	virtual void setSize(QPair<int, int> size) { size_ = size; }
	virtual void setWidth(int width) { size_.first = width; }
	virtual void setHeight(int height) { size_.second = height; }
	virtual void setImageSource(const QString&);
	virtual void setMoving(bool moving) { moving_ = moving; }
	virtual void setTeam(Team team) { team_ = team; }
	virtual void setHealth(int health) = 0;
	virtual void setPower(int power) { power_ = power; }
	virtual void setShield(int shield) { shield_ = shield; }
	virtual void setBehavior(Behavior*);

	~MapObject();

signals:
	void positionChanged();
	void imageSourceChanged();
	void directionChanged();

protected:
	QPoint		position_ {};    //pxMap
	int			layer_ {};
	Direction	direction_ {};
	QPair<int, int> size_ {};
	QString		imageSource_ {};
	bool		moving_ {};
	Team		team_ {};
	int			health_ {};
	int			power_ {};
	int			shield_ {};
	Behavior*	behavior_ {};
};

#endif // MAPOBJECT_H
