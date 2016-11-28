#ifndef CLI_VIEW_H
#define CLI_VIEW_H

#include "view.h"
#include "../model/entity/character.h"
#include "../model/entity/baseCharacters.h"
#include "../model/entity/entity.h"
#include "../model/game.h"
#include "../model/grid.h"
#include "../model/cell.h"
#include <memory>

class CLIView : View {

	std::weak_ptr<Character> mPlayer;
	std::shared_ptr<Game> mGame;
	void printGrid();
public:
	CLIView(std::shared_ptr<Character>, std::shared_ptr<Game>);
	~CLIView();
	void notify(CharacterDeath &) override;
	void notify(CharacterAttack &) override;
	void notify(EntityMoved &) override;
	void notify(EntityCreated &) override;
	void notify(EntityRemoved &) override;
	void notify(EntityObserved &) override;
	void notify(ItemUsed &) override;
	void notify(ItemPickedUp &) override;
	void notify(GridCreated &) override;
	void notify(DebugMessage &) override;
};

#endif // CLI_VIEW_H
