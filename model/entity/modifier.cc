#include "character.h"
#include "modifier.h"
#include <memory>

using namespace std;

Modifier::Modifier(shared_ptr<Character> component): mComponent{component} { }

Modifier::~Modifier() { }
