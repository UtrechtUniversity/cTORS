#pragma once
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>
#include <string>
using namespace std;

#ifndef DEFINE_EXCEPTION
#define DEFINE_EXCEPTION(name, exp_str) \
class name : public exception \
{ \
private: \
	const string message; \
public: \
	name() = default; \
	name(const string& message) : message(string(exp_str) + " " + message) {}; \
	~name() = default; \
	inline virtual const char* what() const throw() override { \
		return message.c_str(); \
	} \
};
#endif

DEFINE_EXCEPTION(ScenarioFailedException, 	"The scenario failed.")
DEFINE_EXCEPTION(InvalidLocationException,	"The location specified is invalid.")
DEFINE_EXCEPTION(InvalidScenarioException,	"The scenariio specified is invalid.")
DEFINE_EXCEPTION(InvalidConfigException, 	"The config file specified is invalid.")
DEFINE_EXCEPTION(InvalidActionException, 	"The action is invalid.")
DEFINE_EXCEPTION(NonExistingPathException, 	"The path does not exist.")

#endif