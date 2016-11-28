#ifndef GAME_H
#define GAME_H

#include "faction.h"
#include <memory>
#include <map>
#include <utility>
#include <vector>
#include "position.h"
#include "grid.h"
#include "../messaging/observer.h"

class GridInit;
class Cell;

class Game {

	std::shared_ptr<Grid> mGrid;
	std::shared_ptr<GridInit> mGridInit;
	std::map<std::pair<FactionId, FactionId>, FactionRelation> mFactionRelation;

public:
	Game();
	~Game();

	void setGridGen(std::shared_ptr<GridInit>);
	void generateNewGrid();
	void createNewEntities();

	std::shared_ptr<Grid> getGrid() const;

	void attach(std::vector<std::shared_ptr<Observer>>);

	void setFactionRelation(FactionId, FactionId, FactionRelation);
	FactionRelation getFactionRelation(FactionId, FactionId) const;

	void turnUpdate();

	GridSize getGridSize() const;
	std::shared_ptr<Cell> getCell(Position) const;
	std::shared_ptr<Cell> getCell(int, int) const;

	void move(std::shared_ptr<Character>, Direction);
	void attack(std::shared_ptr<Character>, Direction);
	void usePotion(std::shared_ptr<Character>, Direction);

};

#endif // GAME_H
