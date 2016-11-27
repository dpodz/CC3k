#ifndef POSITION_H
#define POSITION_H

enum Direction {
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
			case NO: return {x + 1, y};
			case NE: return {x + 1, y + 1};
			case EO: return {x, y + 1};
			case SE: return {x - 1, y + 1};
			case SO: return {x - 1, y};
			case SW: return {x - 1, y - 1};
			case WO: return {x, y - 1};
			case NW: return {x + 1, y - 1};
		}
	}
};

#endif // POSITION_H
