#ifndef POSITION_H
#define POSITION_H

enum class Direction {
	NO,
	NE,
	EO,
	SE,
	SO,
	SW,
	WO,
	NW
};

struct Position {
	int x, y;

	Position calcPosInDirection(Direction offset) {
		switch (offset) {
			case Direction::NO: return {x + 1, y};
			case Direction::NE: return {x + 1, y + 1};
			case Direction::EO: return {x, y + 1};
			case Direction::SE: return {x - 1, y + 1};
			case Direction::SO: return {x - 1, y};
			case Direction::SW: return {x - 1, y - 1};
			case Direction::WO: return {x, y - 1};
			case Direction::NW: return {x + 1, y - 1};
		}
		return {x,y};
	}
};

#endif // POSITION_H
