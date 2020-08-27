/**
* Contains the definition of the RadioCarSimulator class
* @file RadioCarSimulator.h
* @author Tobias Johansson
* @date 2020-08-26
*/

#pragma once

#include <vector>

#include "Room.h"
#include "MonsterTruck.h"
#include "OffroadCar.h"
#include "SportTrackCar.h"
#include "Command.h"

class RadioCarSimulator
{
public:
	RadioCarSimulator();
	~RadioCarSimulator();

	void initialize();
	void run();
	void analyzeResult();

private:
	bool roomSetup();
	bool carSetup();
	bool commandsSetup();

	bool carInBounds();
	void executeCommandOnCar(Command command);

	Room m_room;
	MonsterTruck m_car;
	std::vector<Command> m_commands;

	bool m_initialized;
	bool m_ranSuccessfully;
	std::string m_reasonForFailedRun;
};

