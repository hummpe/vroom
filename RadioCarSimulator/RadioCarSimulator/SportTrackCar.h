/**
* Contains the definition of the SportTrackCar class
*
* @file SportTrackCar.h
* @author Tobias Johansson
* @date 2020-08-26
*/

#pragma once

#include "Car.h"
class SportTrackCar :
	public Car
{
public:
	SportTrackCar();
	SportTrackCar(float diameter, const Position2D& startingPosition, Heading heading);
	~SportTrackCar();
};

