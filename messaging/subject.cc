//Subject.cc
#include <memory>
#include <vector>
#include "message.h"

void Subject::attach( std::shared_ptr<Observer> observer) {
	mObservers.push(observer);
}

void Subject::notifyObservers(BaseMessage & message) {
	for (auto & observer : mObservers) {
		message.notifyObserver(observer);
	}
}


