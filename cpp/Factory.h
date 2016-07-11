#ifndef FACTORY_H
#define FACTORY_H

#include "Map.h"

class GameController;

class Factory : public QObject
{
	Q_OBJECT

public:
	explicit Factory(QObject*, GameController*);

protected:
	GameController* gameController_;
};

#endif // FACTORY_H
