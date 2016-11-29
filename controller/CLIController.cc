#include <memory>
#include <iostream>
#include <string>
#include "CLIController.h"
#include "controller.h"
#include "../model/game.h"
#include "../model/position.h"
#include "../model/entity/baseCharacters.h"
#include "../init/gridInitRandomGen.h"
#include "../view/CLIView.h"
#include "../messaging/observer.h"

using namespace std;

CLIController::CLIController(shared_ptr<Game> game): Controller {game} { }

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

	cout << "Game starts" << endl;

	string filename = "default.map";

	mPlayer = make_shared<Shade>();
	// Generate new grid
	auto view = make_shared<CLIView>(mPlayer, mGame); 
	
	vector<shared_ptr<Observer>> observers(3);
	observers.push_back(view);
	observers.push_back(mGame->getGrid());
	observers.push_back(shared_from_this());

	mPlayer->attach(observers);

	auto gridInit = make_shared<GridInitRandomGen>(mPlayer, filename, observers);

	mGame->setGridGen(gridInit);
	
	mGame->generateNewGrid();

	mGame->attach(observers);

	mGame->createNewEntities();


	// player moves
	view->updateView();
	cout << "Enter a valid command: ";

	string cmd;
	while (cin >> cmd) {

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
		}

		view->updateView();
		view->turnUpdate();
		cout << "Enter a valid command: ";
	}
}


bool CLIController::gameCycle() {
	// TODO:
	return false;
}
