#ifndef CELL_H
#define CELL_H

#include "../messaging/subject.h"
#include "position.h"
#include <memory>
#include <vector>

enum class CellType {
	Empty,
	Floor,
	Wall,
	Door,
	Passage,
	Stair
};

typedef int RoomId;

class Entity;
class Character;

class Cell : public Subject {

	std::vector<std::shared_ptr<Entity>> mEntities;
	CellType mCellType;
	RoomId mRoomId;
	const Position mCellPos;

public:
	Cell(Position cellPos = {-1,-1});
	~Cell();

	std::vector<std::shared_ptr<Entity>> getEntities() const;
	CellType getType() const;
	void setType(CellType);

	Position getPos() const;

	RoomId getRoomId() const;
	void setRoomId(RoomId);
	
	std::shared_ptr<Character> getCharacter() const;
	bool isValidMove() const;

	void addEntity(std::shared_ptr<Entity>);
	void removeEntity(std::shared_ptr<Entity>);
	void purgeEntities();

	void walkedOn(std::shared_ptr<Character>);
	void lookedOn(std::shared_ptr<Character>);
	void usePotion(std::shared_ptr<Character>);

	void turnUpdate();
};

#endif // CELL_H
