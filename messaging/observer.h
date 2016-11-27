#ifndef OBSERVER_H
#define OBSERVER_H

#include "messages.h"
#include "defaultMessages.h"
class Observer {
	
public:
	Observer();
	virtual ~Observer() = 0;

	// Due to constraints with C++ we must have seperate notify per message
	// Can't just override function for specific subclass
	virtual void notify(CharacterDeath &);
	virtual void notify(CharacterAttack &);
	virtual void notify(EntityMoved &);
	virtual void notify(EntityCreated &);
	virtual void notify(EntityRemoved &);
	virtual void notify(EntityObserved &);
	virtual void notify(ItemUsed &);
	virtual void notify(ItemPickedUp &);
	virtual void notify(MapCreated &);
	virtual void notify(DebugMessage &);
};

#endif // OBSERVER_H
