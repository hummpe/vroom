/**
* Contains the entry point to the RadioCarSimulator program
*
* @file main.cpp
* @author Tobias Johansson
* @date 2020-08-26
*/

#include "RadioCarSimulator.h"

int main()
{
	RadioCarSimulator rcs;
	rcs.initialize();
	rcs.run();
	rcs.analyzeResult();

	system("pause");
	return 0;
}