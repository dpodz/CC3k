#include <memory>
#include <iostream>
#include <string>
#include <exception>
#include "CLIController.h"
#include "controller.h"
#include "../model/game.h"
#include "../model/position.h"
#include "../model/entity/baseCharacters.h"
#include "../init/gridInitRandomGen.h"
#include "../init/gridInitPreset.h"

#include "../view/CLIView.h"
#include "../messaging/observer.h"
#include "../messaging/subject.h"
#include "../messaging/messages.h"

using namespace std;

CLIController::CLIController(shared_ptr<Game> game, string fileName,
	bool usePreset): Controller (game, make_shared<CLIView>(nullptr, nullptr)), 
  mPlayer {}, mFileName (fileName), mUsePreset (usePreset) { }

CLIController::~CLIController() { }

const map <string, Direction> strToDir { 
	{"no", Direction::NO},
	{"so", Direction::SO},
	{"ea", Direction::EA},
	{"we", Direction::WE},
	{"ne", Direction::NE},
	{"nw", Direction::NW},
	{"se", Direction::SE},
	{"sw", Direction::SW}
};

void CLIController::playGame() {

	cout << "Select a Race" << endl;

	// TODO: Race selection here



	mPlayer = make_shared<Shade>();
	// Generate new grid
	mView = make_shared<CLIView>(mPlayer, mGame); 
	
	auto observers = make_shared<vector<shared_ptr<Observer>>>(3);
	observers->push_back(mView);
	observers->push_back(shared_from_this());

	shared_ptr<GridInit> gridInit;

	if (mUsePreset) {
		gridInit = make_shared<GridInitPreset>(mPlayer, mFileName, observers);
	}
	else {
		gridInit = make_shared<GridInitRandomGen>(mPlayer, mFileName, observers);
	}
	
	mGame->setGridGen(gridInit);
	mGame->generateNewGrid();

	observers->push_back(mGame->getGrid());

	mPlayer->attach(*observers);
	shared_from_this()->attach(*observers);
	mGame->attach(*observers);

	mGame->createNewEntities();

	// player moves
	mView->updateView();
	mView->turnUpdate();
	cout << "Enter a valid command: ";

	string cmd;
	while (cin >> cmd) {
		bool valid = true;
		try {
			if (cmd == "q") return;

			else if (cmd == "no" || cmd == "so" || cmd == "ea" || cmd == "we" 
				|| cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw") {
				mGame->move(mPlayer, strToDir.at(cmd));
			} else if (cmd == "a") {
				string dir;
				cin >> dir;
				mGame->attack(mPlayer, strToDir.at(dir));
			} else if (cmd == "u") {
				string dir;
				cin >> dir;
				mGame->usePotion(mPlayer, strToDir.at(dir));
			} else if (cmd == "r") {

			} else if (cmd == "f") {

			} else {
				throw invalid_argument("");
			}
		}
		catch (exception) {
			DebugMessage msg ("Invalid command entered");
			notifyObservers(msg);
			valid = false;
		}

		if (valid) {
			bool gameOver = gameCycle();
			if (gameOver) {
				mView->updateView();
				break;
			}
		}

		mView->updateView();
		mView->turnUpdate();

		cout << "Enter a valid command: ";
	}
}


bool CLIController::gameCycle() {
	return false;
}
