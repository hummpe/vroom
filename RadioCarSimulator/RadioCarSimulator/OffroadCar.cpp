/**
* Contains the implementation of the OffroadCar class
*
* @file OffroadCar.cpp
* @author Tobias Johansson
* @date 2020-08-26
*/

#include "OffroadCar.h"

OffroadCar::OffroadCar()
	: Car{ 1.5f, Position2D(0.0f, 0.0f), Heading::UNDEFINED, "OffroadCar" }
{
}

OffroadCar::OffroadCar(float diameter, const Position2D & startingPosition, Heading heading)
	: Car{ diameter, startingPosition, heading, "OffroadCar" }
{
}

OffroadCar::~OffroadCar()
{
}
