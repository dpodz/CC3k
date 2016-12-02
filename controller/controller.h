#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include "../messaging/observer.h"

class Game;
class View;

class Controller : public Observer {

protected:
	std::shared_ptr<Game> mGame;
	std::shared_ptr<View> mView;

public:
	Controller();
	~Controller();

	virtual void playGame() = 0;
	virtual void gameCycle() = 0;
};

#endif // CONTROLLER_H
