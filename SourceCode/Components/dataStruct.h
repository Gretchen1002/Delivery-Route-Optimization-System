#pragma once
#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include<stdbool.h>
#include"mapping.h"
#define MAX_WEIGHT 5000
#define MAX_VOLUME 250
#define MAX_PACKAGES 500

/*size and weight for each package*/
struct Package {
	float size;
	float weight;
};


/*data for each truck*/
struct Truck {
	char color[10];	//truck blue, yellow or green
	struct Package packages[MAX_PACKAGES];	//an array of packages 
	int numPackages;		//how many packages this truck carries
	float availableW;	//remaining available weight of this truck
	float availableV;	//remaining available volume of this truck
};


/*track shipment details of each package*/
struct ShipmentDetails {
	struct Package package;	//details of "this" package
	struct Point destination;	//where this package goes to

};

#endif // !DATASTRUCT_H

