#include <memory>
#include <iostream>
#include <string>
#include "CLIController.h"
#include "controller.h"
#include "../model/game.h"
#include "../model/position.h"
#include "../model/entity/baseCharacters.h"
#include "../init/gridInit.h"
#include "../init/gridInitPreset.h"

using namespace std;

CLIController::CLIController(shared_ptr<Game> game): Controller{game} { }

CLIController::~CLIController() { }

const map <string, Direction> strToDir { 
  {"no", Direction::NO},
  {"ne", Direction::NE},
  {"eo", Direction::EO},
  {"se", Direction::SE},
  {"so", Direction::SO},
  {"sw", Direction::SW},
  {"wo", Direction::WO},
  {"nw", Direction::NW},
};

void CLIController::playGame() {

	cout << "Game starts" << endl;

	string filename = "floorPlan.txt";

	mPlayer = make_shared<Shade>();
    // generate new grid
    shared_ptr<GridInit> gridInit = make_shared<GridInitPreset>(mPlayer, filename);
    mGame->setGridGen(gridInit);
    //mGame->generateNewGrid();
    mGame->createNewEntities();


    // player moves

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
    }
}


bool CLIController::gameCycle() {
	// TODO:
	return false;
}
