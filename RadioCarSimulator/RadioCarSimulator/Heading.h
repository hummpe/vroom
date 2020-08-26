#pragma once

#include <string>

enum class Heading : int
{
	N,
	S,
	E,
	W,
	UNDEFINED
};

static std::string HeadingToString(Heading h)
{
	switch (h)
	{
	case Heading::N:
		return "N";
	case Heading::S:
		return "S";
	case Heading::E:
		return "E";
	case Heading::W:
		return "W";
	default:
		return "UNDEFINED";
	}
}

static Heading StringToHeading(const std::string& s)
{
	if (s == "N")
		return Heading::N;
	else if (s == "S")
		return Heading::S;
	else if (s == "E")
		return Heading::E;
	else if (s == "W")
		return Heading::W;
	else
		return Heading::UNDEFINED;
}