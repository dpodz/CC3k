#ifndef WOUNDATK_H
#define WOUNDATK_H

#include "stats.h"
#include "potion.h"

class WoundAtk: public Potion {
public:
        WoundAtk(): Potion{Stats{-5,0,0,0}} { }
        ~WoundAtk() { }

};

#endif
