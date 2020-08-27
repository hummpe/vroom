/**
* Contains the implementation of the MonsterTruck class
*
* @file MonsterTruck.cpp
* @author Tobias Johansson
* @date 2020-08-26
*/

#include "MonsterTruck.h"

MonsterTruck::MonsterTruck()
	: Car{ 1.0f, Position2D(0.0f, 0.0f), Heading::UNDEFINED, "MonsterTruck" }
{
}

MonsterTruck::MonsterTruck(float diameter, const Position2D & startingPosition, Heading heading)
	: Car{ diameter, startingPosition, heading, "MonsterTruck" }
{
}

MonsterTruck::~MonsterTruck()
{
}
