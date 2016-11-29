#include <memory>
#include "item.h"
#include "entity.h"
#include "../../messaging/messages.h"
#include "../../messaging/subject.h"

Item::Item() { }

Item::~Item() { }

bool Item::canWalkOn() {return true;}

void Item::itemUsedBy(std::shared_ptr<Character> character) { }
