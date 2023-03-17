/**************************************************************************************************
 Name        : Mini Project 1
 Author      : Mina Sobhy Kamel
 Description : Vehicle Control system
 **************************************************************************************************/

#include <stdio.h>
#define WITH_ENGINE_TEMP_CONTROLLER 1

//Function prototype
void start(void);
void Want_To(void);
void TrafficLight(void);
void TempSensor(void);
void EngineSensor (void);

//GLobal variables
char input  = 0;
char turnOn = 0;
char traffic_light = 0;

//putting values for off and on state
enum state { OFF , ON };

//struct declaration
struct car{
	int  vehicle_speed;
	enum state AC;
	enum state Engine_Temperature_Controller;
	float roomtemp;
	float enginetemp;
};

//Struct initialization
struct car vehicle1 = {0, OFF, OFF, 35, 90};

//starting function definitions
//initially choose what the vehicle does
void start(void)
{
	do
	{
		printf("Please choose a,b or c (lowerCase only)\n");
		printf("a. Turn on the vehicle engine\n");
		printf("b. Turn off the vehicle engine\n");
		printf("c. Quit the system\n\n");
		fflush(stdout);
		scanf(" %c", &input);
	}
	while(input != 'a' && input != 'b' && input != 'c');

	Want_To();
}

//choose what the engine does after it started
void Want_To(void)
{
	if ('b' == input)
	{
		printf("Turn off the vehicle engine\n\n");
	}
	else if ('c' == input)
	{
		printf("Quit the system\n\n");
		return ;
	}
	else
	{
		while (turnOn != 'a')
		{
			do
			{
#if WITH_ENGINE_TEMP_CONTROLLER
				printf("\nPlease choose a, b, c or d (lowerCase only)\n");
#else
				printf("Please choose a, b or c (lowerCase only)\n");
#endif
				printf("a. Turn off the engine\n");
				printf("b. Set the traffic light color\n");
				printf("c. Set the room temperature (Temperature Sensor)\n");
#if WITH_ENGINE_TEMP_CONTROLLER
				printf("d. Set the engine temperature (Engine Temperature Sensor)\n\n");
#endif
				fflush(stdout);
				scanf(" %c", &turnOn);
			}
			while(turnOn != 'a' && turnOn != 'b' && turnOn != 'c' && turnOn != 'd');

			if('a' == turnOn)
			{
				printf("Turn off the engine\n\n");
				break;
			}
			else if('b' == turnOn)
			{
				printf("Set the traffic light color\n\n");
				TrafficLight();

			}
			else if ('c' == turnOn)
			{
				printf("Set the room temperature (Temperature Sensor)\n\n");
				TempSensor();
			}
#if WITH_ENGINE_TEMP_CONTROLLER
			else
			{
				printf("Set the engine temperature (Engine Temperature Sensor)\n\n");
				EngineSensor();
			}
#else
			if (turnOn == 'd')
				continue;
#endif
			if (30 == vehicle1.vehicle_speed)
			{
				if (turnOn == 'b' || turnOn == 'c')
				{
					vehicle1.AC = ON;
					vehicle1.roomtemp = vehicle1.roomtemp * (5.0/4.0) +1 ;
				}
#if WITH_ENGINE_TEMP_CONTROLLER
				if (turnOn == 'b' || turnOn == 'd' )
				{
					vehicle1.Engine_Temperature_Controller = ON;
					vehicle1.enginetemp = vehicle1.enginetemp * (5.0/4.0) +1 ;
				}
#endif
			}
			printf("Engine state: ON\n");
			vehicle1.AC? printf("AC: ON \n"): printf("AC: OFF \n");
			printf("Vehicle Speed: %d Km/Hr\n", vehicle1.vehicle_speed);
			printf("Room Temperature: %f C\n", vehicle1.roomtemp);
#if WITH_ENGINE_TEMP_CONTROLLER
			vehicle1.Engine_Temperature_Controller? printf("Engine Temperature Controller: ON \n"): printf("Engine_Temperature_Controller: OFF \n");
			printf("Engine Temperature: %f C\n", vehicle1.enginetemp);
#endif
		}
	}
	turnOn = 0;
	input =0;
	start();
}

//selecting speed according to color of the traffic light
void TrafficLight(void)
{
	char light = 0;
	do
	{
		printf("Enter the traffic light color (G,O,R) \n");
		fflush(stdout);
		scanf(" %c", &light);
	}
	while(light != 'G' && light != 'g' && light != 'O' && light != 'o' && light != 'R' && light != 'r');

	if ('G' == light || 'g' == light)
		vehicle1.vehicle_speed = 100;
	else if ('O' == light || 'o' == light)
		vehicle1.vehicle_speed = 30;
	else
		vehicle1.vehicle_speed =0;
}

//turning on or off the AC according to the temperature sensor
void TempSensor(void)
{
	printf("Enter the room temperature\n");
	fflush(stdout);
	scanf(" %f", &vehicle1.roomtemp);

	if (vehicle1.roomtemp < 10 || vehicle1.roomtemp > 30)
	{
		vehicle1.AC = ON;
		vehicle1.roomtemp = 20;
	}
	else
	{
		vehicle1.AC = OFF;
	}
}

//limiting the temperature of the engine depending on the current temperature
void EngineSensor (void)
{
#if WITH_ENGINE_TEMP_CONTROLLER
	printf("Enter the engine temperature\n");
	fflush(stdout);
	scanf(" %f", &vehicle1.enginetemp);

	if (vehicle1.enginetemp < 100 || vehicle1.enginetemp > 150)
	{
		vehicle1.Engine_Temperature_Controller = ON;
		vehicle1.enginetemp = 125;
	}
	else
	{
		vehicle1.Engine_Temperature_Controller = OFF;
	}
#endif
}

int main()
{

	start();

	return 0;
}
