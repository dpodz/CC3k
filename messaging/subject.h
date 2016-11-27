#ifndef SUBJECT_H
#define SUBJECT_H

#include "message.h"
#include <vector>
#include <memory>

class Observer;

class Subject {

	std::vector<std::strong_ptr<Observer>> mObservers;

public:
	Subject();
	// ~Subject() is still implemented
	virtual ~Subject() = 0; 

	void attach(std::shared_ptr<Observer>);
	void notifyObservers(BaseMessage &);
};

#endif // SUBJECT_H
