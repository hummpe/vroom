#include "RadioCarSimulator.h"

#include <string>
#include <iostream>


RadioCarSimulator::RadioCarSimulator()
	: m_initialized {false}, m_ranSuccessfully {false}
{
}


RadioCarSimulator::~RadioCarSimulator()
{
}

void RadioCarSimulator::initialize()
{
	std::cout << "RadioCarSimulator - Setup" << std::endl;
	if (!roomSetup())
	{
		// Room setup failed
		return;
	}

	if (!carSetup())
	{
		// Car setup failed
		return;
	}

	if (!commandsSetup())
	{
		// Command setup failed
		return;
	}
	
	m_initialized = true;
}

void RadioCarSimulator::run()
{
	std::cout << "RadioCarSimulator - Running" << std::endl;

	if (!m_initialized)
	{
		// Simulator has not been initialized, or has failed initialization
		std::cout << "The simulator has not been initalized, or has failed initialization" << std::endl;
		m_reasonForFailedRun = "Initialization failed";
		return;
	}
	 

	// Iterate over commands and apply them to the car one by one
	for (Command command : m_commands)
	{
		executeCommandOnCar(command);

		std::cout << m_car.getPosition() << std::endl;

		if (!carInBounds())
		{
			// Latest command sent car out of bounds!
			m_reasonForFailedRun = "Car went out of bounds after moving " + CommandToString(command);
			m_ranSuccessfully = false;
			return;
		}
	}


	m_ranSuccessfully = true;
}

void RadioCarSimulator::analyzeResult()
{
	if (!m_ranSuccessfully)
	{
		std::cout << "Simulation failed." << std::endl;
		std::cout << "Reason: " << m_reasonForFailedRun << std::endl;
		std::cout << "End position of the car: " << m_car.getPosition() << std::endl;
		std::cout << "Heading of car: " << HeadingToString(m_car.getHeading()) << std::endl;
	}
	else
	{
		std::cout << "Simulation ran successfully." << std::endl;
		std::cout << "End position of the car: " << m_car.getPosition() << std::endl;
		std::cout << "Heading of car: " << HeadingToString(m_car.getHeading()) << std::endl;
	}
}

bool RadioCarSimulator::roomSetup()
{
	int widthOfRoom = -1;
	int depthOfRoom = -1;

	// 1. Ask about size of the room
	std::cout << "Size of room (<width><space><depth>): ";
	try
	{
		// TODO: Get full line, since expected input is <integer><space><integer> ?
		std::cin >> widthOfRoom;

		// TODO: Expand error checking, and "clear" cin..?
		if (widthOfRoom < 0)
			throw std::invalid_argument{ "Bad input - Width of room is excpected to be a positive integer" };

		std::cin >> depthOfRoom;

		if (depthOfRoom < 0)
			throw std::invalid_argument{ "Bad input - Depth of room is excpected to be a positive integer" };

		m_room.setWidth(widthOfRoom);
		m_room.setDepth(depthOfRoom);

		// "Clean up" cin buffer
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	catch (const std::exception& e)
	{
		std::cout << "[RadioCarSimulator::roomSetup] Exception caught! Details: " << e.what() << std::endl;
		return false;
	}

	return true;
}

bool RadioCarSimulator::carSetup()
{
	int startPositionX = 0;
	int startPositionY = 0;
	std::string startHeadingString = "";
	Heading startHeading = Heading::UNDEFINED;

	std::cout << "Starting position and heading of car (<x><space><y><space><heading>): ";
	try
	{
		std::cin >> startPositionX;

		if (startPositionX < 0 || startPositionX > m_room.getWidth())
			throw std::invalid_argument{ "Bad input - X position is not an integer between 0 and the width of the room" };

		std::cin >> startPositionY;

		if (startPositionY < 0 || startPositionY > m_room.getDepth())
			throw std::invalid_argument{ "Bad input - Y position is not an integer between 0 and the depth of the room" };

		std::cin >> startHeadingString;
		startHeading = StringToHeading(startHeadingString);

		if(startHeading == Heading::UNDEFINED)
			throw std::invalid_argument{ "Bad input - Heading is not of known format {N, S, E, W}" };

		m_car.getPosition().setX(startPositionX);
		m_car.getPosition().setY(startPositionY);
		m_car.setHeading(startHeading);

		if(!carInBounds())
			throw std::invalid_argument{ "Bad input - The car is out of bounds of the room" };

		// "Clean up" cin buffer
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	catch (const std::exception& e)
	{
		std::cout << "[RadioCarSimulator::carSetup] Exception caught! Details: " << e.what() << std::endl;
		return false;
	}


	return true;
}

bool RadioCarSimulator::commandsSetup()
{
	std::string commands = "";

	std::cout << "Enter a series of commands: ";

	std::getline(std::cin, commands);

	try
	{
		if (commands.length() == 0)
			throw std::invalid_argument("Bad input - No commands given in command series");

		for (char c : commands)
		{
			Command commandFromSeries = CharToCommand(c);
			if (commandFromSeries == Command::UNDEFINED)
				throw std::invalid_argument("Bad input - Invalid command '" + std::string(1, c) + "' in command series");

			m_commands.push_back(commandFromSeries);
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "[RadioCarSimulator::commandsSetup] Exception caught! Details: " << e.what() << std::endl;
		return false;
	}

	return true;
}

bool RadioCarSimulator::carInBounds()
{
	// The bounds of the room
	float roomWidth = static_cast<float>(m_room.getWidth());
	float roomDepth = static_cast<float>(m_room.getDepth());

	// The car can be treated as a round object with an X meter diameter

	// Find center-point of car
	float radiusOfCar = static_cast<float>(m_car.getDiameter()) / 2.0f;
	float centerPointX = m_car.getPosition().getX() + radiusOfCar;
	float centerPointY = m_car.getPosition().getY() + radiusOfCar;
	
	try
	{
		// Check if in bounds along x-axis
		if (centerPointX < 0)
			throw std::invalid_argument("Center point X of car is below 0, out of bounds of the room");

		if (centerPointX > roomWidth)
			throw std::invalid_argument("Center point X of car is exceeding the width of the room, out of bounds");

		// Inside western wall
		if (centerPointX < radiusOfCar)
			throw std::invalid_argument("The car is inside the western wall, out of bounds of the room");

		// Inside eastern wall
		if (centerPointX > (roomWidth - radiusOfCar))
			throw std::invalid_argument("The car is inside the eastern wall, out of bounds of the room");

		// Check if in bounds along y-axis
		if (centerPointY < 0)
			throw std::invalid_argument("Center point Y of car is below 0, out of bounds of the room");

		if (centerPointY > roomDepth)
			throw std::invalid_argument("Center point Y of car is exceeding the depth of the room, out of bounds");

		// Inside north wall
		if (centerPointY < radiusOfCar)
			throw std::invalid_argument("The car is inside the north wall, out of bounds");

		// Inside south wall
		if (centerPointX > (roomDepth - radiusOfCar))
			throw std::invalid_argument("The car is inside the south wall, out of bounds");
	}
	catch (const std::exception& e)
	{
		std::cout << "[RadioCarSimulator::CarInBounds] Exception caught! Details: " << e.what() << std::endl;
		return false;
	}

	return true;
}

void RadioCarSimulator::executeCommandOnCar(Command command)
{
	if (command == Command::UNDEFINED)
	{
		// TODO: BAD COMMAND - error handling
		return;
	}

	switch (command)
	{
	case Command::F:
		// Move car in the current heading 1m
		m_car.moveForwards(1.0f);
		break;
	case Command::B:
		// Move car opposite way of the current heading 1m
		m_car.moveBackwards(1.0f);
		break;
	case Command::L:
		// Rotate car 90 degrees counter clockwise
		m_car.rotateCounterClockwise();
		break;
	case Command::R:
		// Rotate car 90 degrees clockwise
		m_car.rotateClockwise();
		break;
	default:
		// Not implemented command
		break;
	}
}
