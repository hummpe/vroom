/**
* Contains the definition of and utility functions for the Command-enum
*
* @file Command.h
* @author Tobias Johansson
* @date 2020-08-26
*/

#pragma once

#include <string>

enum class Command : int
{
	F,
	B,
	L,
	R,
	UNDEFINED
};

static std::string CommandToString(Command c)
{
	switch (c)
	{
	case Command::F:
		return "F";
	case Command::B:
		return "B";
	case Command::L:
		return "L";
	case Command::R:
		return "R";
	default:
		return "UNDEFINED";
	}
}

static Command StringToCommand(const std::string& s)
{
	if (s == "F")
		return Command::F;
	else if (s == "B")
		return Command::B;
	else if (s == "L")
		return Command::L;
	else if (s == "R")
		return Command::R;
	else
		return Command::UNDEFINED;
}

static Command CharToCommand(char s)
{
	if (s == 'F')
		return Command::F;
	else if (s == 'B')
		return Command::B;
	else if (s == 'L')
		return Command::L;
	else if (s == 'R')
		return Command::R;
	else
		return Command::UNDEFINED;
}