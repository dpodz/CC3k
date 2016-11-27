#ifndef RANDOM_AI_H
#define RANDOM_AI_H

#include "AI.h"
#include <memory>

class Game;
class Character;

class randomAI : public AI {

public:
	randomAI(std::shared_ptr<Game>);
	~randomAI();

	virtual void processTurn(std::shared_ptr<Character>) override;
};

#endif // RANDOM_AI_H
