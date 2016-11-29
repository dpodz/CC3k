#ifndef BOOSTDEF_H
#define BOOSTDEF_H

#include "stats.h"
#include "potion.h"

class BoostDef: public Potion {
public:
        BoostDef(): Potion{Stats{0,5,0,0}} { }
        ~BoostDef() { }

};

#endif
