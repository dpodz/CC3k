#ifndef GAME_H
#define GAME_H

#include "faction.h"
#include <memory>
#include <map>
#include <utility>
#include "position.h"

class Grid;
class GridInit;
class Cell;

class Game {

	std::unique_ptr<Grid> mGrid;
	std::shared_ptr<GridInit> mGridInit;
	std::map<std::pair<FactionId, FactionId>, FactionRelation> mFactionRelation;

public:
	Game();
	~Game();

	void setGridGen(std::shared_ptr<GridInit>);
	void generateNewGrid();
	void createNewEntities();

	void setFactionRelation(FactionId, FactionId, FactionRelation);
	FactionRelation getFactionRelation(FactionId, FactionId) const;

	void turnUpdate();

	GridSize getGridSize() const;
	std::shared_ptr<Cell> getCell(int, int) const;

	void move(std::shared_ptr<Character>, Direction);
	void attack(std::shared_ptr<Character>, Direction);
	void usePotion(std::shared_ptr<Character>, Direction);
};

#endif // GAME_H
