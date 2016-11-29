#include "CLIView.h"
#include <iostream>
#include <map>
#include <stdlib.h>
using namespace std;

CLIView::CLIView(shared_ptr<Character> player, shared_ptr<Game> game):
	mPlayer {player}, mGame {game} {}

CLIView::~CLIView() {}

void CLIView::printGrid() {
	
	// This is OS dependent
	system("clear");

	if (!mGame) {
		cout << "No grid loaded yet" << endl;
		return;
	}
	//USE GRID SIZE
	for (int i = 0 ; i < 30 ; i++) {
		for (int j = 0 ; j < 79 ; j++) {
			CellType cellType = mGame->getCell(j,i)->getType();

			if (mGame->getCell(j,i)->getEntities().size() > 0) {
				cout << "T"; // TODO PLACEHOLDER FOR ANY ENTITY
			} else if (cellType == CellType::Wall) {
				cout << "|"; // TODO Add logic for | and -
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
	
	cout << killerName << " killed " << killedName << endl;
	//updateView(vector<Position>{cd.killer->getPos, cd.killed->getPos});
}

//TODO
void CLIView::notify(CharacterAttack & ca) {
	cout << "A character attacked another character for " << ca.damage << " damage!" << endl;
}

//TODO
void CLIView::notify(ItemUsed & iu) {
	cout << "A character used an item" << endl;
}

//TODO
void CLIView::notify(EntityCreated & ec) {
	cout << "An entity was created" << endl;
	printGrid();
	//updateView(vector<Position>
}

//TODO
void CLIView::notify(EntityRemoved & er) {
	cout << "An entity was removed" << endl;
	printGrid();
}

//TODO
void CLIView::notify(GridCreated & mc) {
	cout << "Grid created" << endl;
	mGame = mc.theGame;
	printGrid();
	//updateView();
}

//TODO
void CLIView::notify(EntityObserved & eo) {
	cout << "An entity observed an entity" << endl;
}

//TODO
void CLIView::notify(ItemPickedUp & ipu) {
	cout << "An item was picked up" << endl;
}

//TODO
void CLIView::notify(EntityMoved & cm) {
	cout << "An entity moved" << endl;
	printGrid();
}
