#include "character.h"
#include "modifier.h"
#include <memory>

using namespace std;

Modifier::Modifier(shared_ptr<StatsContainer> component, Stats stats): 
	StatsContainer{stats}, mComponent {component} { }

Modifier::~Modifier() { }

Stats Modifier::getBaseStats() const {
	return mComponent->getBaseStats();
}
