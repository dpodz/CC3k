#ifndef AI_H
#define AI_H

#include <memory>
#include "../../state/game.h"
#include "../../state/entity/character.h"

class CharacterAI {
	std::shared_ptr<Game> game;

public:

	CharacterAI(std::shared_ptr<Game>);
	~CharacterAI();

	virtual void processTurn(std::shared_ptr<Character>) = 0;

};

#endif // AI_H
