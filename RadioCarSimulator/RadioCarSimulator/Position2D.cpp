#include "Position2D.h"



Position2D::Position2D()
{
	Position2D(0, 0);
}

Position2D::Position2D(float x, float y)
	: m_x {x}, m_y {y}
{
}


Position2D::~Position2D()
{
}

float Position2D::getX() const
{
	return m_x;
}

float Position2D::getY() const
{
	return m_y;
}

void Position2D::setX(float x)
{
	m_x = x;
}

void Position2D::setY(float y)
{
	m_y = y;
}

std::ostream & operator<<(std::ostream & out, const Position2D & p)
{
	out << "(" << p.getX() << ", " << p.getY() << ")";
	return out;
}
