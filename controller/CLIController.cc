#include <memory>
#include <iostream>
#include <string>
#include <exception>
#include "CLIController.h"
#include "controller.h"
#include "ai/randomAI.h"
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

CLIController::CLIController(string fileName,
	bool usePreset): Controller {}, 
  mPlayer {}, mFileName (fileName), mUsePreset (usePreset), mLevel {0} { }

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

string CLIController::raceSelection() {
	string race = "";
	
	cout << "Select a race: " << endl;
	while (cin >> race) {
		if (race == "s") {
			mPlayer = make_shared<Shade>();
			break;
		} else if (race == "d") {
			mPlayer = make_shared<Drow>();
			break;
		} else if (race == "v") {
			mPlayer = make_shared<Vampire>();
			break;
		} else if (race == "t") {
			mPlayer = make_shared<Troll>();
			break;
		} else if (race == "g") {
			mPlayer = make_shared<Goblin>();
			break;
		} else if (race == "q") {
			return "";
		} else {
			cout << "Select a race: " << endl;
		}
	}	
	return race;
}

void CLIController::gameSetup() {

	mGame = make_shared<Game>();
	mView = make_shared<CLIView>(mPlayer, mGame); 
	mAI = make_shared<RandomAI>(mGame);
	
	auto observers = make_shared<vector<weak_ptr<Observer>>>(4);
	observers->push_back(mView);
	observers->push_back(shared_from_this());
	observers->push_back(mAI);

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

	GridCreated gc {mGame};
	notifyObservers(gc);

	InfoMessage im {"PC has spawned."};
	notifyObservers(im);

	// setting default factions
	mGame->setFactionRelation(2,1,FactionRelation::hostile);
	mGame->setFactionRelation(3,1,FactionRelation::hostile);
	mLevel = 1;
}

bool CLIController::nextLevel() {
	if (mLevel == 5) {
		return false;
	} 

	mGame->purgeEntities();
	mGame->createNewEntities();

	GridCreated gc {mGame};
	notifyObservers(gc);

	InfoMessage im {"PC has taken the stairs to the next level."};
	notifyObservers(im);

	++mLevel;
	return true;
}

void CLIController::playGame() {

	if (raceSelection() == "") return;

	gameSetup();

	mView->updateView();
	mView->turnUpdate();

	cout << "Enter a valid command: ";

	bool runGameCycle = true; 

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

				if (raceSelection() == "") return;
				gameSetup();
				
				InfoMessage msg {"Restarting Game."};
				notifyObservers(msg);

				// Avoids touching anything that modifies game state
				// Until player does valid command
				valid = false;

			} else if (cmd == "f") {
				runGameCycle = !runGameCycle;
			} else {
				throw invalid_argument("");
			}
		}
		catch (exception) {
			InfoMessage msg ("Invalid command entered.");
			notifyObservers(msg);
			valid = false;
		}

		if (mGame->getCell(mPlayer->getPos())->getType() == CellType::Stair) {
			if (!nextLevel()) {
				InfoMessage msg {"PC has cleared the dungeon. You Win!"};
				notifyObservers(msg);
				InfoMessage scr {"Final score is " + to_string(mPlayer->getScore())};
				notifyObservers(scr);
				mView->updateView();
				return;
			}
			valid = false;
		}

		if (valid) {

			mGame->turnUpdate();
			
			if (runGameCycle) {
				gameCycle();
			}
		}

		if (mPlayer->getHealth() <= 0) {
			InfoMessage msg {"You lost :("};
			notifyObservers(msg);
			mView->updateView();
			return;
		}

		mView->updateView();
		mView->turnUpdate();
	}
}


void CLIController::gameCycle() {

	// Computer players make moves
	vector<shared_ptr<Character>> computerPlayers;
	for (int y = 0 ; y < mGame->getGridSize().y ; ++y) {
		for (int x = 0 ; x < mGame->getGridSize().x ; ++x) {
			try {
				shared_ptr<Character> charCheck = mGame->getCell(x,y)->getCharacter();
				if (charCheck != mPlayer) {
					computerPlayers.emplace_back(charCheck); 
				}
			}
			catch (...) { }
		}
	}

	for (auto & character : computerPlayers) {
		mAI->processTurn(character);
	}
}
