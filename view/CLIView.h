#ifndef CLI_VIEW_H
#define CLI_VIEW_H

#include "view.h"
#include <memory>

class Character;
class Game;

class CLIView : View {

	std::weak_ptr<Character> mPlayer;
	std::shared_ptr<Game> mGame;

public:
	CLIView(std::shared_ptr<Character>, std::shared_ptr<Game>);
	~CLIView();
};

#endif // CLI_VIEW_H
