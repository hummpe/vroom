/**
* Contains the implementation of the RadioCarSimulator class
* @file RadioCarSimulator.cpp
* @author Tobias Johansson
* @date 2020-08-26
*/

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
	std::cout << "RadioCarSimulator - Running simulation on:" << std::endl;
	std::cout << "Car type: " << m_car.getType() << std::endl;
	std::cout << "Starting position: " << m_car.getPosition() << std::endl;
	std::cout << "Car size/diameter: " << m_car.getDiameter() << std::endl;

	if (!m_initialized)
	{
		// Simulator has not been initialized, or has failed initialization
		std::cout << "The simulator has not been initalized, or has failed initialization" << std::endl;
		m_reasonForFailedRun = "Initialization failed";
		return;
	}
	 

	// Iterate over commands and apply them to the car one by one
	int commandNr = 0;
	bool printEachStep = false;
	for (Command command : m_commands)
	{
		executeCommandOnCar(command);

		if (printEachStep)
		{
			std::cout << ++commandNr << ": "
				<< "Position: " << m_car.getPosition()
				<< " Heading: " << HeadingToString(m_car.getHeading())
				<< std::endl;
		}

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
	int widthOfRoom = 0;
	int depthOfRoom = 0;

	// 1. Ask about size of the room
	std::cout << "Enter size of room (<width><space><depth>): ";
	try
	{
		// TODO: Get full line (getline) instead, and either tokenize and try to convert to unsigned int
		// or regex to see if it matches "<width><space><depth>

		std::cin >> widthOfRoom;

		if(widthOfRoom <= 0
			|| std::cin.fail())
			throw std::invalid_argument{ "Bad input - Width of room is excpected to be a positive integer" };

		std::cin >> depthOfRoom;

		if (depthOfRoom <= 0
			|| std::cin.fail())
			throw std::invalid_argument{ "Bad input - Depth of room is excpected to be a positive integer" };

		// "Clean up" cin buffer
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		
		// Neither widthOfRoom or depthOfRoom should be able
		// to be negative at this point
		// Set the values read from user input
		m_room.setWidth(static_cast<int>(widthOfRoom));
		m_room.setDepth(static_cast<int>(depthOfRoom));

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
	float startPositionX = -0.1f;
	float startPositionY = -0.1f;
	std::string startHeadingString = "";
	Heading startHeading = Heading::UNDEFINED;

	std::cout << "Enter starting position and heading of car (<x><space><y><space><heading>): ";
	try
	{
		// TODO: Get full line (getline) instead, and either tokenize and try to convert to wanted data type
		// or regex to see if it at least matches "<x><space><y><space><heading>"

		std::cin >> startPositionX;

		if (startPositionX < 0.0f
			|| startPositionX > static_cast<float>(m_room.getWidth())
			|| std::cin.fail())
			throw std::invalid_argument{ "Bad input - X position is not a floating point number between 0.0 and the width of the room" };

		std::cin >> startPositionY;

		if (startPositionY < 0.0f
			|| startPositionY > static_cast<float>(m_room.getDepth())
			|| std::cin.fail())
			throw std::invalid_argument{ "Bad input - Y position is not not a floating point number between 0 and the depth of the room" };

		std::cin >> startHeadingString;
		startHeading = StringToHeading(startHeadingString);

		if(startHeading == Heading::UNDEFINED)
			throw std::invalid_argument{ "Bad input - Heading is not of known format {N, S, E, W}" };

		// "Clean up" cin buffer
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');

		// Set the values read from user input
		m_car.getPosition().setX(startPositionX);
		m_car.getPosition().setY(startPositionY);
		m_car.setHeading(startHeading);

		if(!carInBounds())
			throw std::invalid_argument{ "Bad input - The car is out of bounds of the room" };
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
	float radiusOfCar = m_car.getDiameter() / 2.0f;
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
		if ((centerPointX - radiusOfCar) < 0)
			throw std::invalid_argument("The car is inside the western wall, out of bounds of the room");

		// Inside eastern wall
		if ((centerPointX + radiusOfCar) > roomWidth)
			throw std::invalid_argument("The car is inside the eastern wall, out of bounds of the room");


		// Check if in bounds along y-axis
		if (centerPointY < 0)
			throw std::invalid_argument("Center point Y of car is below 0, out of bounds of the room");

		if (centerPointY > roomDepth)
			throw std::invalid_argument("Center point Y of car is exceeding the depth of the room, out of bounds");

		// Inside south wall
		if ((centerPointX - radiusOfCar) < 0)
			throw std::invalid_argument("The car is inside the south wall, out of bounds");

		// Inside north wall
		if ((centerPointY + radiusOfCar) > roomDepth)
			throw std::invalid_argument("The car is inside the north wall, out of bounds");
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
