#include "Room.h"



Room::Room()
{
	Room(10, 10);
}

Room::Room(unsigned int width, unsigned int depth)
	: m_width {width}, m_depth{depth}
{
}


Room::~Room()
{
}

unsigned int Room::getWidth()
{
	return m_width;
}

void Room::setWidth(unsigned int width)
{
	m_width = width;
}

unsigned int Room::getDepth()
{
	return m_depth;
}

void Room::setDepth(unsigned int depth)
{
	m_depth = depth;
}
