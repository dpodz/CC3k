#ifndef RANDOM_AI_H
#define RANDOM_AI_H

#include "characterAI.h"
#include <memory>

class Game;
class Character;

class RandomAI : public CharacterAI {

public:
	RandomAI(std::shared_ptr<Game>);
	~RandomAI();

	virtual void processTurn(std::shared_ptr<Character>) override;
};

#endif // RANDOM_AI_H
