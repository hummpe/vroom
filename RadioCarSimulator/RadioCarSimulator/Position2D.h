/**
* Contains the definition of the Position2D class
* @file Position2D.h
* @author Tobias Johansson
* @date 2020-08-26
*/

#pragma once

#include <iostream>

class Position2D
{
public:
	Position2D();
	Position2D(float x, float y);
	~Position2D();

	friend std::ostream & operator << (std::ostream &out, const Position2D &p);

	float getX() const;
	float getY() const;
	void setX(float x);
	void setY(float y);
private:
	float m_x;
	float m_y;
};

