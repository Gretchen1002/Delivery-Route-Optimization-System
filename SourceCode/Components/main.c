#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mapping.h"
#include "dataStruct.h"
#include "deliver.h"


int main(void)
{
	//initialize base map with routes
	struct Map baseMap = populateMap();

	//add 3 routes to the base map
	struct Route blueRoute = getBlueRoute();
	struct Route greenRoute = getGreenRoute();
	struct Route yellowRoute = getYellowRoute();
	struct Route routes[] = { blueRoute, greenRoute, yellowRoute };

	//add the blue route first
	struct Map routeMap = addRoute(&baseMap, &blueRoute);
	//add green & yellow
	routeMap = addRoute(&routeMap, &greenRoute);
	routeMap = addRoute(&routeMap, &yellowRoute);

	//print map with all 3 routes
	printMap(&routeMap, 1, 1);

	//initialze trucks to empty state
	struct ShipmentDetails cargo = {0};
	struct Truck truckBlue;
	struct Truck truckYellow;
	struct Truck truckGreen;
	initializeTruck(&truckBlue, "BLUE");
	initializeTruck(&truckGreen, "GREEN");
	initializeTruck(&truckYellow, "YELLOW");
	struct Truck trucks[] = { truckBlue, truckGreen,truckYellow };

	//display for expected output
	printf("\n");
	printf("=================\n"
		"Seneca Polytechnic Deliveries:\n"
		"=================\n");
	int getInput = 1;
	int numTrucks = 3;

	//take user input
	do 
	{
		// Get user input & validate input
		getInput = getUserInput(&cargo); 
		if (getInput == 1) 
		{
		
			// find best truck for the shipment based on route and load
			int validTruckIndex = findTruck4Shipment(&baseMap, routes, trucks, numTrucks, &cargo); 

			// show which truck is selected
			switch (validTruckIndex) {
			case 0:
				printf("Ship on BLUE LINE, ");
				//Displays the diversion route for the truck, if needed
				displayDiversion(&routeMap, &routes[0], &cargo.destination);
				addPackageToTruck(&trucks[0], &cargo.package);
				break;
			case 1:
				printf("Ship on GREEN LINE, ");
				displayDiversion(&routeMap, &routes[1], &cargo.destination);
				addPackageToTruck(&trucks[1], &cargo.package);
				break;
			case 2:
				printf("Ship on YELLOW LINE, ");
				displayDiversion(&routeMap, &routes[2], &cargo.destination);
				addPackageToTruck(&trucks[2], &cargo.package);
				break;
			default:
				printf("There is no avaliable truck, will be shipped tomorrow\n");
				break;
			}
		}
	}while (getInput != 0);
	return 0;
}
