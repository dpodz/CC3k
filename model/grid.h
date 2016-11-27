#ifndef GRID_H
#define GRID_H

#include "../messaging/observer.h"
#include "../messaging/subject.h"
#include <memory>
#include <vector>

class Cell;
class Character;

struct GridSize {
	int x, y;
};

class Grid : public Observer, public Subject {

	GridSize mSize;
	std::vector<std::vector<std::shared_ptr<Cell>>> mCells;

public:
	Grid(GridSize);
	~Grid();

	void turnUpdate();

	GridSize getGridSize() const;
	std::shared_ptr<Cell> getCell(int, int) const;

	void move(std::shared_ptr<Character>, Direction);
	void attack(std::shared_ptr<Character>, Direction);
	void usePotion(std::shared_ptr<Character>, Direction);
};

#endif // GRID_H
