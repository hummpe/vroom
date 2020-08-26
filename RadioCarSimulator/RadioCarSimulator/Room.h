#pragma once
class Room
{
public:
	Room();
	Room(unsigned int width, unsigned int depth);
	~Room();

	unsigned int getWidth();
	void setWidth(unsigned int width);
	unsigned int getDepth();
	void setDepth(unsigned int depth);

private:
	unsigned int m_width;
	unsigned int m_depth;
};

