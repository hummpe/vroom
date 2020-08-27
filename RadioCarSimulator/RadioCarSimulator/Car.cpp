/**
* Contains the implementation of the Car class
* @file Car.cpp
* @author Tobias Johansson
* @date 2020-08-26
*/

#include "Car.h"

Car::Car()
{
	Car( 1.0f, Position2D(0.0f, 0.0f), Heading::UNDEFINED, "Car" );
}

Car::Car(float diameter, const Position2D & startingPosition, Heading heading, std::string type)
	: m_diameter {diameter}, 
	m_position {startingPosition},
	m_heading {heading},
	m_type {type}
{
}

Car::~Car()
{
}

float Car::getDiameter() const
{
	return m_diameter;
}

void Car::setDiameter(float diameter)
{
	m_diameter = diameter;
}

Position2D& Car::getPosition()
{
	return m_position;
}

void Car::setPosition(Position2D position)
{
	m_position = position;
}

Heading Car::getHeading() const
{
	return m_heading;
}

void Car::setHeading(Heading heading)
{
	m_heading = heading;
}

std::string Car::getType() const
{
	return m_type;
}

void Car::setType(std::string type)
{
	m_type = type;
}

void Car::moveForwards(float meter)
{
	switch (m_heading)
	{
	case Heading::N:
		m_position.setY(m_position.getY() + meter);
		break;
	case Heading::S:
		m_position.setY(m_position.getY() - meter);
		break;
	case Heading::E:
		m_position.setX(m_position.getX() + meter);
		break;
	case Heading::W:
		m_position.setX(m_position.getX() - meter);
		break;
	case Heading::UNDEFINED:
		break;
	default:
		// Not implemented heading
		break;
	}
}

void Car::moveBackwards(float meter)
{
	// Use moveForward but with changed sign (+/-) on distance
	moveForwards(meter * -1.0f);
}

void Car::rotateCounterClockwise()
{
	switch (m_heading)
	{
	case Heading::N:
		m_heading = Heading::W;
		break;
	case Heading::S:
		m_heading = Heading::E;
		break;
	case Heading::E:
		m_heading = Heading::N;
		break;
	case Heading::W:
		m_heading = Heading::S;
		break;
	case Heading::UNDEFINED:
		break;
	default:
		// Not implemented heading
		break;
	}
}

void Car::rotateClockwise()
{
	switch (m_heading)
	{
	case Heading::N:
		m_heading = Heading::E;
		break;
	case Heading::S:
		m_heading = Heading::W;
		break;
	case Heading::E:
		m_heading = Heading::S;
		break;
	case Heading::W:
		m_heading = Heading::N;
		break;
	case Heading::UNDEFINED:
		break;
	default:
		// Not implemented heading
		break;
	}
}
