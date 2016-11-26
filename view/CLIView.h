#ifndef CLI_VIEW_H
#define CLI_VIEW_H

#include "view.h"
#include "../state/entity/chracter.h"
#include <memory>

class CLIView : View {

	std::weak_ptr<Character> mPlayer;

public:
	CLIView(std::shared_ptr<Character>);
	~CLIView();
};

#endif // CLI_VIEW_H
