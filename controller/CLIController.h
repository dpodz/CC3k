#ifndef CLI_CONTROLLER_H
#define CLI_CONTROLLER_H

#include "controller.h"
#include <memory>

class Game;
class Character;

class CLIController : public Controller {

	std::shared_ptr<Character> mPlayer;

public:
	CLIController(std::shared_ptr<Game>);
	~CLIController();
	
	virtual void playGame() override;
	virtual bool gameCycle() override;
};

#endif // CLI_CONTROLLER_H
