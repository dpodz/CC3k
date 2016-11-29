#ifndef POSITION_H
#define POSITION_H

enum class Direction {
	NO,
	SO,
	EA,
	WE,
	NE,
	NW,
	SE,
	SW
};

struct Position {
	int x, y;

	Position calcPosInDirection(Direction offset) {
		switch (offset) {
			case Direction::NO: return {x, y - 1};
			case Direction::SO: return {x, y + 1};
			case Direction::EA: return {x + 1, y};
			case Direction::WE: return {x - 1, y};
			case Direction::NE: return {x + 1, y - 1};
			case Direction::NW: return {x - 1, y - 1};
			case Direction::SE: return {x + 1, y + 1};
			case Direction::SW: return {x - 1, y + 1};
		}
		return {x,y};
	}
};

#endif // POSITION_H
