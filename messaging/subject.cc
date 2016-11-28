//Subject.cc
#include <memory>
#include <vector>
#include "messages.h"
#include "observer.h"
#include "subject.h"

using namespace std;

Subject::Subject() : mObservers {} {}

Subject::~Subject() {}

void Subject::attach(shared_ptr<Observer> observer) {
	mObservers.push_back(observer);
}

void Subject::attach(vector<shared_ptr<Observer>> observers) {
	for (auto & observer : observers) {
		attach(observer);
	}
}

void Subject::notifyObservers(BaseMessage & message) {
	for (auto & w_observer : mObservers) {
		if (auto observer = w_observer.lock()) {
			message.notifyObserver(observer);
		}
	}
}


