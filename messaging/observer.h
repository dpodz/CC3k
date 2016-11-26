#ifndef OBSERVER_H
#define OBSERVER_H

#include "messages.h"

class Observer {
public:

	Observer();
	virtual ~Observer() = 0;

	// Due to constraints with C++ we must have seperate notify per message
	// Can't just override function for specific subclass
	notify(CharacterDeath &);
	notify(CharacterAttack &);
	notify(CharacterMoved &);
	notify(EntityCreated &);
	notify(EntityObserved &);
	notify(ItemUsed &);
	notify(ItemPickedUp &);
	notify(MapCreated &);
	notify(DebugMessage &);
};

#endif // OBSERVER_H
