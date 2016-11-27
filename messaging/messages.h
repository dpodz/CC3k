#ifndef MESSAGES_H
#define MESSAGES_H

class Observer;

struct BaseMessage {
	virtual notifyObserver( std::shared_ptr<Observer> ) = 0;
};

#endif //MESSAGES_H
