#ifndef CLI_CONTROLLER_H
#define CLI_CONTROLLER_H

#include "controller.h"
#include "../../state/game.h"
#include "../../state/entity/character.h"
#include <memory>

class CLIController : public Controller {

	std::weak_ptr<Character> mPlayer;

public:
	CLIController(std::shared_ptr<Game>);
	~CLIController();
	
	virtual void playGame() override;
	virtual bool gameCycle() override;
};

#endif // CLI_CONTROLLER_H
