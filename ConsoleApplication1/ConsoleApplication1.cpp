// MissileText.cpp : Defines the entry point for the console application.

//


#include "stdafx.h"

#include <iostream>

#include <string>



std::string getMissileName(enum WarHead warHead);

bool launchCodeInput();



typedef struct Position

{

	int x;

	int y;


	void print()

	{

		std::cout << x <<", " << y << std::endl;

	}


}Coordinates;


enum WarHead { EXPLOSIVE, NUCLEAR };


typedef struct Enemy {

	Coordinates coordinates;

}Target;




struct Missile {

	WarHead payload;


	Coordinates coordinates;


	Target target;


	bool armed = false;


	void arm()

	{

		if (armed)

			armed = false;

		else

			armed = true;

	}


	void update() {

		coordinates.x += 1;

		coordinates.y += 2;

	}

};





int main()

{

	Missile missile;

	while (missile.armed == false)
	{


		//Initialise missile position
		missile.coordinates.x = 0;
		missile.coordinates.y = 0;



		// Set PayLoad



		int payloadSelect;


		std::cout << "Choose Pay Load: 1 = EXPLOSIVE, 2 = NUCLEAR" << std::endl;

		std::cin >> payloadSelect;


		// Prevent invalid entries

		while (payloadSelect > 2 || payloadSelect < 1)

		{


			std::cout << "Invalid Entry!!!" << std::endl;

			std::cout << "Choose Pay Load: 1 = EXPLOSIVE, 2 = NUCLEAR" << std::endl;

			std::cin >> payloadSelect;

		}


		// Set warheads

		if (payloadSelect == 1)

		{

			missile.payload = EXPLOSIVE;

		}

		else

		{

			missile.payload = NUCLEAR;

		}


		// Relay message of warhead being set

		std::cout << getMissileName(missile.payload) << " head set!!!" << std::endl;


		// ENd payload select


		// BEGIN Find Target

		int xRadarPos = 0;

		int yRadarPos = 0;



		// Set Trargets position



		missile.target.coordinates.x = 40;
		missile.target.coordinates.y = 120;





		std::cout << "Use radar to find target!" << std::endl;




		std::cout << "Input an X coordinate:";

		std::cin >> xRadarPos;



		std::cout << "Input a Y coordinate:";

		std::cin >> yRadarPos;





		// distance formula

		float distance = sqrtf(pow((xRadarPos - missile.target.coordinates.x), 2)

			+ pow((yRadarPos - missile.target.coordinates.y), 2));



		// if distance further than 50 m retry again 

		while (distance > 50)

		{


			std::cout << "Could not find target try again!" << std::endl;
			std::cout << "Radar suggests it was " << std::to_string(distance) << " meters from finding target." << std::endl;
			std::cout << std::endl;

			std::cout << "Use radar to find target!" << std::endl;


			std::cout << "Input an X coordinate:";

			std::cin >> xRadarPos;



			std::cout << "Input a Y coordinate:";

			std::cin >> yRadarPos;


			distance = sqrtf(pow((xRadarPos - missile.target.coordinates.x), 2) +

				pow((yRadarPos - missile.target.coordinates.y), 2));


		}



		// Print Target ocation

		std::cout << "Found target at: ";

		missile.target.coordinates.print();

		//END FInd target





		// Enter Launch Code

		if (launchCodeInput() == true)

		{

			missile.arm();

		}


		// set distance of 

		float distanceMissile = sqrtf(pow((missile.coordinates.x - missile.target.coordinates.x), 2) +

			pow((missile.coordinates.y - missile.target.coordinates.y), 2));

		float collisionAllowance = 0;

		if (missile.payload == NUCLEAR)
		{
			collisionAllowance = 50;
		}
		else if (missile.payload == EXPLOSIVE)
		{
			collisionAllowance = 5;
		}

		while (distanceMissile > collisionAllowance)

		{

			distanceMissile = sqrtf(pow((missile.coordinates.x - missile.target.coordinates.x), 2) +

				pow((missile.coordinates.y - missile.target.coordinates.y), 2));


			missile.update();


			missile.coordinates.print();

			if (distanceMissile > 1000)

			{

				std::cout << " Missile missed, missile disarmed. You failed try again!!!" << std::endl;
				missile.arm();
				break;

			}



		}

		if (distanceMissile < 50)

		{

			std::cout << "Target within blast Radius... Detonated... Collision Detected Destroyed Target Confirmation!!!" << std::endl;

		}

	}


	system("pause");

	return 0;

}



std::string getMissileName(enum WarHead warHead)

{

	switch (warHead)

	{

	case EXPLOSIVE: return "Explosive";

	case NUCLEAR: return "NUCLEAR";

	}

}










bool launchCodeInput()

{

	int pass = 0;



	while (pass != 1450)

	{

		std::cout << "Enter password(Hint: 200 + 1250):";

		std::cin >> pass;

	}


	return true;

}