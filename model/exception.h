#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

class EntityNotFound : public std::runtime_error {
public:
	EntityNotFound(const std::string& str): std::runtime_error{str} {}
};

#endif // EXCEPTION_H
