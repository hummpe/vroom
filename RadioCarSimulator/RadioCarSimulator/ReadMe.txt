-------------------------------------------
--- Simulator for radio controlled cars ---
-------------------------------------------

Estimated time used: 5.5h

Assumptions:
-	The room size is given in whole meters
	(integers, unsigned even since negative size
	does not really make sense) according to the
	description/test - 
	However: the position, diameter and movement
	of the car have been given a floating point value.

	Rationale/reason: The "room" could be made
	out of distinct tiles/built like a grid, but
	the car could be of "any" size and have the
	ability of moving "any" number of centi-/deci-/
	meters on a single command - maybe dependant on
	which type it is. Which means that it, dependant
	on size and movement could occupy non-integer
	positions/coordinates of the room.

-	The (registered) position/coordinate of the
	car/round object differs from the round objects
	center point - to adhere with the notion of
	[0, 0] being the southwest most point of the room
	where the car will fit
	Example: Position = [0, 0], diameter = 1 =>
	CenterPointOfCar = [0.5, 0.5]

	Have to say that I got quite hung up on the
	figure of the 4x4 meter sized room with the
	highlighted position of [0, 0] in the test.
	This leads to (given a diameter of 1) possible
	positions ranging from 0 <-> 3 in the x- and
	y-axis

	

TODO:
-	Add more descriptive comments in the "logic heavy"
	parts

-	Replace all cin with a better way of getting
	user input.

-	Create Log "utility class" to write everything "through"
	For easier formating/adding timestamps if wanted/
	changing output to other than cout easier

Notes:
-	I should have just gone with getline(...) for getting
	all of the user input - would have made it easier to
	validate input data. I know that my validation misses a
	bunch of cases (eg Room size input: 1 1 1 slips
	through) and I would not have had to clear cin-buffer.

-	Prepared for the Off-road and Sport track car types
	aswell (and tested)
	(Just gave them a bit different default diameters etc,
	"for fun", however - they all move the same distance
	on a single command for now)

-	Should have redone the logic regarding positions,
	and let the position of the car be cars "center point".
	

