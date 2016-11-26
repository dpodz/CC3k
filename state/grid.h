#ifndef GRID_H
#define GRID_H

#include "cell.h"
#include "../messaging/observer.h"
#include "../messaging/subject.h"
#include <memory>
#include <vector>

class Grid : public Observer, public Subject {

	std::vector<std::vector<std::shared_ptr<Cell>>> mCells;
	GridSize mSize;

public:
	Grid(GridSize);
	~Grid();
	
	void move(std::shared_ptr<Character>, Direction);
	void attack(std::shared_ptr<Character>, Direction);
	void usePotion(std::shared_ptr<Character>, Direction);

	void turnUpdate();

	std::shared_ptr<Cell> getCell(int, int) const;
	GridSize getGridSize() const;
};

#endif // GRID_H
