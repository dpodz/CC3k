#ifndef AI_H
#define AI_H

#include <memory>
#include "../../messaging/observer.h"

class Character;
class Game;

class CharacterAI : public Observer {

protected:
	std::shared_ptr<Game> mGame;

public:
	CharacterAI(std::shared_ptr<Game>);
	~CharacterAI();

	virtual void processTurn(std::shared_ptr<Character>) = 0;
};

#endif // AI_H
