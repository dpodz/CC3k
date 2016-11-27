//Subject.cc
#include <memory>
#include <vector>
#include "message.h"
#include "observer.h"
#include "subject.h"

Subject::Subject() : mObservers {} {}

~Subject::Subject() {}

void Subject::attach( std::shared_ptr<Observer> observer) {
	mObservers.push(observer);
}

void Subject::notifyObservers(BaseMessage & message) {
	for (auto & w_observer : mObservers) {
		if (auto observer = w_observer.lock()) {
			message.notifyObserver(observer);
		}
	}
}


