#include <memory>
#include "controller.h"
#include "../model/entity/character.h"
#include "../model/game.h"

using namespace std;

Controller::Controller(shared_ptr<Game> game, shared_ptr<View> view):
	mGame{game}, mView {view} { }

Controller::~Controller() { }
