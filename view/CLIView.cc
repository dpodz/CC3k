#include "CLIView.h"
#include "../model/grid.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <stdlib.h>
using namespace std;

CLIView::CLIView(shared_ptr<Character> player, shared_ptr<Game> game):
	mPlayer {player}, mGame {game}, mMessages {} {}

CLIView::~CLIView() {}

bool CLIView::checkIfVerticalWall(int x, int y) {

	if (y > 0 ) {
		if (mGame->getCell(x,y-1)->getType() == CellType::Wall) {
			return true;
		}
	}

	if (y < mGame->getGridSize().y - 1) {
		if (mGame->getCell(x,y+1)->getType() == CellType::Wall) {
			return true;
		}
	}

	return false;
}

void CLIView::printGrid() {

	if (!mGame) {
		cout << "No grid loaded yet" << endl;
		return;
	}

	// TODO: Use grid size
	for (int y = 0 ; y < 25 ; ++y) {
		for (int x = 0 ; x < 79 ; ++x) {
			CellType cellType = mGame->getCell(x,y)->getType();

			if (mGame->getCell(x,y)->getEntities().size() > 0) {
				cout << "T"; // TODO PLACEHOLDER FOR ANY ENTITY
			} else if (cellType == CellType::Wall) {
				if (checkIfVerticalWall(x, y)) {
					cout << "|";
				}
				else {
					cout << "-";
				}
			} else if (cellType == CellType::Floor) {
				cout << ".";
			} else if (cellType == CellType::Door) {
				cout << "+";
			} else if (cellType == CellType::Passage) {
				cout << "#";
			} else if (cellType == CellType::Stair) {
				cout << "\\";
			} else {
				cout << " ";
			}
		}
		cout << endl;
	}


	ostringstream raceLine {};

	raceLine << "Race: " << typeid(*mPlayer).name()
		<< " Gold: " << mPlayer->getGold();

	cout << setw(70) << left << raceLine.str()
		<< "Floor: ???" << endl;

	Stats charStats = mPlayer->getStats();

	cout << "HP: " << mPlayer->getHealth() << endl;
	cout << "Atk: " << charStats.attack << endl;
	cout << "Def: " << charStats.defence << endl;
	cout << "Action: " << mMessages.str() << endl;
}

void CLIView::updateView() {
	// This is OS dependent
	system("clear");
	printGrid();

}

void CLIView::turnUpdate() {
	mMessages.str("");
}

void CLIView::notify(DebugMessage & dm) {
	cout << "Debug Message: " << dm.message << endl;
}

void CLIView::notify(CharacterDeath & cd) {
	string killerName;
	string killedName;
	
	if (dynamic_pointer_cast<Shade>(cd.killer)) { killerName = "Shade"; } 
	else { killerName = "Not a Shade"; }
	
	if (dynamic_pointer_cast<Shade>(cd.killed)) { killedName = "Shade"; }
	else { killerName = "Not a Shade"; }
	
	mMessages << killerName << " killed " << killedName << ". ";
	//updateView(vector<Position>{cd.killer->getPos, cd.killed->getPos});
}

//TODO
void CLIView::notify(CharacterAttack & ca) {
	mMessages << "A character attacked another character for " << ca.damage << " damage! ";
}

//TODO
void CLIView::notify(ItemUsed & iu) {
	mMessages << "A character used an item. ";
}

//TODO
void CLIView::notify(EntityCreated & ec) {
	mMessages << "An entity was created. ";
}

//TODO
void CLIView::notify(EntityRemoved & er) {
	mMessages << "An entity was removed. ";
}

//TODO
void CLIView::notify(GridCreated & mc) {
	mMessages << "Grid created. ";
	mGame = mc.theGame;
}

//TODO
void CLIView::notify(EntityObserved & eo) {
	mMessages << "An entity observed an entity. ";
}

//TODO
void CLIView::notify(ItemPickedUp & ipu) {
	mMessages << "An item was picked up. ";
}

//TODO
void CLIView::notify(EntityMoved & cm) {
	mMessages << "An entity moved. ";
}
