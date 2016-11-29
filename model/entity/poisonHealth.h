#ifndef POISONHEALTH_H
#define POISONHEALTH_H

#include "stats.h"
#include "potion.h"

class PoisonHealth: public Potion {
public:
        PoisonHealth();
        ~PoisonHealth();

        void itemUsedBy(std::shared_ptr<Character>) override;
};

#endif
