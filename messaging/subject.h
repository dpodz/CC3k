#ifndef SUBJECT_H
#define SUBJECT_H

#include "observer.h"
#include "message.h"
#include <vector>
#include <memory>

class Subject {

	std::vector<std::shared_ptr<Observer>> observers;

public:

	Subject();
	// ~Subject() is still implemented
	virtual ~Subject() = 0; 

	void attach(std::shared_ptr<Observer>);
	void notifyObservers(BaseMessage &);
};

#endif // SUBJECT_H
