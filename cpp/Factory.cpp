#include "Factory.h"

Factory::Factory(QObject* parent, GameController* gameController)
	: QObject(parent), gameController_(gameController)
{}
