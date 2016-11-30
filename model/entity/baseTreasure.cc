#include "baseTreasure.h"
#include <memory>
#include "treasure.h"
#include "baseCharacters.h"

using namespace std;

SmallGold::SmallGold(): Treasure(1) { }

SmallGold::~SmallGold() { }

NormalGold::NormalGold(): Treasure(2) { }

NormalGold::~NormalGold() { }

MerchantHoard::MerchantHoard(): Treasure(4) { }

MerchantHoard::~MerchantHoard() { }

DragonHoard::DragonHoard(): Treasure(6), attachedDragon {} {}

DragonHoard::~DragonHoard() {}

void DragonHoard::setDragon(shared_ptr<Dragon> dragon) {
	attachedDragon = dragon;
}

void DragonHoard::walkedOnBy(shared_ptr<Character> character) {
	if (attachedDragon.expired()) {
		Treasure::walkedOnBy(character);
	}
}
