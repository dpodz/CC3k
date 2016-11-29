#include "baseTreasure.h"
#include <memory>
#include "treasure.h"

NormalGold::NormalGold(): Treasure(2) { }

NormalGold::~NormalGold() { }


MerchantHoard::MerchantHoard(): Treasure(4) { }

MerchantHoard::~MerchantHoard() { }
