#include "character.h"
#include "modifier.h"
#include <memory>

using namespace std;

Modifier::Modifier(shared_ptr<StatsContainer> component): mComponent{component} { }

Modifier::~Modifier() { }

Stats Modifier::getBaseStats() {
	return component->getBaseStats();
}
