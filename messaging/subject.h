#ifndef SUBJECT_H
#define SUBJECT_H

#include "messages.h"
#include <vector>
#include <memory>

class Observer;

class Subject {

	std::vector<std::weak_ptr<Observer>> mObservers;

public:
	Subject();
	// ~Subject() is still implemented
	virtual ~Subject() = 0; 

	void attach(std::weak_ptr<Observer>);
	void attach(std::vector<std::weak_ptr<Observer>>);
	void notifyObservers(BaseMessage &);
};

#endif // SUBJECT_H
