#ifndef RANDOM_AI_H
#define RANDOM_AI_H

#include "AI.h"
#include "../../state/game.h"
#include "../../state/entity/character.h"
#include <memory>

class randomAI : public AI {

public:
	randomAI(std::shared_ptr<Game>);
	~randomAI();

	virtual void processTurn(std::shared_ptr<Character>) override;
};

#endif // RANDOM_AI_H
