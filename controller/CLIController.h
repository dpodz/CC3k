#ifndef CLI_CONTROLLER_H
#define CLI_CONTROLLER_H

#include "controller.h"
#include <memory>
#include <string>
#include "../messaging/subject.h"

class Game;
class Character;
class CharacterAI;

class CLIController : public Controller, public Subject,
	public std::enable_shared_from_this<CLIController> {

	std::shared_ptr<CharacterAI> mAI;
	std::shared_ptr<Character> mPlayer;
	std::string mFileName;
	bool mUsePreset;
	int mLevel;

	std::string raceSelection();
	void gameSetup();
	bool nextLevel();

public:
	CLIController(std::string, bool);
	~CLIController();
	
	virtual void playGame() override;
	virtual void gameCycle() override;
};

#endif // CLI_CONTROLLER_H
