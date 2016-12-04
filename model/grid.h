#ifndef GRID_H
#define GRID_H

#include "../messaging/observer.h"
#include "../messaging/subject.h"
#include <memory>
#include <vector>

class Cell;
class Character;

struct GridSize {
	int x;
	int y;
};

class Grid : public Observer, public Subject {

	GridSize mSize;
	std::vector<std::vector<std::shared_ptr<Cell>>> mCells;
	std::vector<std::weak_ptr<Observer>> mObservers;

	bool checkBounds(Position);

public:
	Grid(GridSize);
	~Grid();

	void turnUpdate();

	GridSize getGridSize() const;

	std::shared_ptr<Cell> getCell(Position) const;
	std::shared_ptr<Cell> getCell(int, int) const;

	void move(std::shared_ptr<Character>, Direction);
	void attack(std::shared_ptr<Character>, Direction);
	void usePotion(std::shared_ptr<Character>, Direction);

	void attachCells(std::vector<std::weak_ptr<Observer>>);

	void purgeEntities();

	virtual void notify(CharacterDeath &) override;
	virtual void notify(ItemPickedUp &) override;
	virtual void notify(ItemUsed &) override;
};

#endif // GRID_H
