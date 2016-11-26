#ifndef VIEW_H
#define VIEW_H

#include "../messaging/observer.h"

class View : public Observer {

public:
	View();
	~View() = 0;
	
};

#endif // VIEW_H
