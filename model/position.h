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

	Position calcDirectionGivenPos(Position oldPos) {
		switch (x - oldPos.x) {
			case -1:
				switch (y - oldPos.y) {
					case -1: return Direction::NW;
					case 0: return Direction::WE;
					case 1: return Direction::SW;
				}
				break;
			case 0:
				switch (y - oldPos.y) {
					case -1: return Direction::NO;
					case 1: return Direction::SO;
				}
				break;
			case 1:
				switch (y - oldPos.y) {
					case -1: return Direction::NE;
					case 0: return Direction::EA;
					case 1: return Direction::SE;
				}
				break;
		}
		return Direction::NO;
	}
};

#endif // POSITION_H
