#include "observer.h"

Observer::Observer() {}

Observer::~Observer() {}

void Observer::notify(CharacterDeath &) {}

void Observer::notify(CharacterAttack &) {}

void Observer::notify(EntityMoved &) {}

void Observer::notify(EntityCreated &) {}

void Observer::notify(EntityRemoved &) {}

void Observer::notify(EntityObserved &) {}

void Observer::notify(ItemUsed &) {}

void Observer::notify(ItemPickedUp &) {}

void Observer::notify(GridCreated &) {}

void Observer::notify(DebugMessage &) {}

void Observer::notify(InfoMessage &) {}
