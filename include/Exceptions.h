


#pragma once
#include <sstream>
#include <string>
#include <iostream>

class InvalidPath :public std::exception
{
public:
	InvalidPath() {};
	~InvalidPath() {};
	const char* what() const noexcept {
		return "\nInvalid path: path file doesn't exist, try again!\n";
	}
};

class FileError :public std::exception
{
public:
	FileError() {};
	~FileError() {};
	const char* what() const noexcept {
		return "\nError at line: ";
	}
};

class WrongCommand :public std::invalid_argument
{
public:
	WrongCommand():std::invalid_argument("the command does not exist \n") {}
};

class WrongFucntion :public std::invalid_argument
{
public:
	WrongFucntion() :std::invalid_argument("the fucntion does not exist \n") {}
};

class WrongArgument :public std::invalid_argument
{
public:
	WrongArgument() :std::invalid_argument("the argument should be integer \n") {}
};

class EmptyArgument :public std::runtime_error
{
public:
	EmptyArgument() :std::runtime_error("the argument can't be empty \n") {}
};

class FewArguments :public std::runtime_error
{
public:
	FewArguments() :std::runtime_error("the number of argument is less than required \n") {}
};

class MoreArguments :public std::runtime_error
{
public:
	MoreArguments() :std::runtime_error("the number of argument is more than required \n") {}
};

class NegativeArgument :public std::invalid_argument
{
public:
	NegativeArgument():std::invalid_argument("the argument cant be negative \n") {}
};




/*
// Checking if file path is valid
class ErrorReached : public std::exception
{
public:
	ErrorReached() {};
	~ErrorReached() {};
	const char* what() const noexcept {
		return "Invalid path !\n";
	}
};

// Check if commands is valid
// if user enter Invalid command, print this message
class InvalidCommand : public std::invalid_argument
{
public:
	InvalidCommand() : std::invalid_argument("Command not Found. Enter a new command or Enter the Word -help-\n") {}
};

// If user enter more inputs for one of the commands
// Print this message .
class MoreThanMaxFuncInputs : public std::runtime_error
{
public:
	MoreThanMaxFuncInputs() : std::runtime_error("Wrong Amount Of Inputs - More Inputs!") {}
};

// Send a message if number of Functions is less than 2
class WrongMinimumResize : public std::runtime_error
{
public:
	WrongMinimumResize() : std::runtime_error("Minimum of 2 Functions For resize") {}
};

// If there is too much Functions
// user need to delete or resize
class WrongMaximumResize : public std::runtime_error
{
public:
	WrongMaximumResize() : std::runtime_error("Too Much Functions. Please Use 'resize' or delete.") {}
};

// If user enter less inputs for one of the commands
// Print this message .
class LessThanMinInputs : public std::runtime_error
{
public:
	LessThanMinInputs() : std::runtime_error("Wrong Amount Of Inputs - Less Inputs!") {}
};
*/