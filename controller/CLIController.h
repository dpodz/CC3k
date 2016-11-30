#ifndef CLI_CONTROLLER_H
#define CLI_CONTROLLER_H

#include "controller.h"
#include <memory>

class Game;
class Character;

class CLIController : public Controller, 
	public std::enable_shared_from_this<CLIController> {

	std::shared_ptr<Character> mPlayer;
	std::string mFileName;
	bool mUsePreset;

public:
	CLIController(std::shared_ptr<Game>, std::string, bool);
	~CLIController();
	
	virtual void playGame() override;
	virtual bool gameCycle() override;
};

#endif // CLI_CONTROLLER_H
