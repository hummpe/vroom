/**
* Contains the implementation of the SportTrackCar class
*
* @file SportTrackCar.cpp
* @author Tobias Johansson
* @date 2020-08-26
*/

#include "SportTrackCar.h"

SportTrackCar::SportTrackCar()
	: Car{ 0.9f, Position2D(0.0f, 0.0f), Heading::UNDEFINED, "SportTrackCar" }
{
}

SportTrackCar::SportTrackCar(float diameter, const Position2D & startingPosition, Heading heading)
	: Car{ diameter, startingPosition, heading, "SportTrackCar" }
{
}

SportTrackCar::~SportTrackCar()
{
}
