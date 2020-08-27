/**
* Contains the definition of the OffroadCar class
*
* @file OffroadCar.h
* @author Tobias Johansson
* @date 2020-08-26
*/

#pragma once

#include "Car.h"

class OffroadCar :
	public Car
{
public:
	OffroadCar();
	OffroadCar(float diameter, const Position2D& startingPosition, Heading heading);
	~OffroadCar();
};

