#ifndef BOOSTATK_H
#define BOOSTATK_H

#include "stats.h"
#include "potion.h"

class BoostAtk: public Potion {
public:
        BoostAtk(): Potion{Stats{5,0,0,0}} { }
        ~BoostAtk() { }

};

#endif
