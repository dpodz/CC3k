#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include "../messaging/observer.h"

class Game;

class Controller : public Observer {

protected:
	std::shared_ptr<Game> mGame;

public:
	Controller(std::shared_ptr<Game>);
	~Controller();

	virtual void playGame() = 0;
	virtual bool gameCycle() = 0;
};

#endif // CONTROLLER_H
