#pragma once

#include <string>

#include "Position2D.h"
#include "Heading.h"

class Car
{
public:
	Car();
	Car(unsigned int diameter, const Position2D& startingPosition, Heading heading, std::string type);
	~Car();

	int getDiameter() const;
	void setDiameter(unsigned int diameter);
	Position2D& getPosition();
	void setPosition(Position2D position);
	Heading getHeading() const;
	void setHeading(Heading heading);
	std::string getType() const;
	void setType(std::string type);

	void moveForwards(float meter);
	void moveBackwards(float meter);
	void rotateCounterClockwise();
	void rotateClockwise();

private:
	unsigned int m_diameter;
	Position2D m_position;
	Heading m_heading;
	std::string m_type;
};

