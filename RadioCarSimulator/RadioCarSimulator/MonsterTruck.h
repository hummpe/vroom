/**
* Contains the definition of the MonsterTruck class
*
* @file MonsterTruck.h
* @author Tobias Johansson
* @date 2020-08-26
*/

#pragma once

#include "Car.h"

class MonsterTruck :
	public Car
{
public:
	MonsterTruck();
	MonsterTruck(float diameter, const Position2D& startingPosition, Heading heading);
	~MonsterTruck();
};

