#ifndef WOUNDDEF_H
#define WOUNDDEF_H

#include "stats.h"
#include "potion.h"

class WoundDef: public Potion {
public:
        WoundDef(): Potion{Stats{0,-5,0,0}} { }
        ~WoundDef() { }

};

#endif
