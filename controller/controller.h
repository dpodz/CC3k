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
	Controller(std::shared_ptr<Game>, std::shared_ptr<View>);
	~Controller();

	virtual void playGame() = 0;
	virtual bool gameCycle() = 0;
};

#endif // CONTROLLER_H
