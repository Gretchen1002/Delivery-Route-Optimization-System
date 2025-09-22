#include <corecrt_memcpy_s.h>
#include <vcruntime_string.h>
#include <stdbool.h>
#ifndef DELIVER_H
#define DELIVER_H


/** Function 1 : validation
* Validate package size and weight and destination if those are deliverable
* @param size - user input package size
* @param weight - user input package weight
* @param destination - user input destination
* @ returns - 1(true) or 0(false) whether user input package and destination is valid
*/
int  validateOrder(const struct Package* package, const struct Point* destination);


/** Function 2 : Decide track
* Determine the tracks by comparing the amount and size of cargo carried by the two tracks
* prioritize truck which can deliver shortest path, then consider cargo
* @param t1 - the track to be compared 1
* @param t2 - the track to be compared 2
* @ returns - 1 or 2 depending on selected track
*/
int selectTrack(const struct Truck* t1, const struct Truck* t2);


/** Function 3: pass one package to a truck, check if it is possible to add, if add successfully, return true,
if fail( the truck is full), return false
* @param truck, which truch will be added the package
* @param package, which pakage want to add in the truck,
* @ returns 1 if the package can be added successfully, otherwise 0
*/
bool addPackageToTruck(struct Truck* truck, const struct Package* package);

/** Function 4: initialize truck before first time use it on the day
* @param truck, which truck want to initialize
* @param color, which color the truck will be set
* @ no return type
*/
void initializeTruck(struct Truck* truck, const char* color);

//new functions added for integration
/**
* prompts for user input for shipment info, then call validateOrder to valid user input
* @param cargo: pointer to the struct ShipmentDetails to store user input
* @returns: 1 if the user input is valid and store; 0 if it's stop condidtion; -1 for invalid input 
*/
int getUserInput(struct ShipmentDetails* cargo);

/**
* find the best truck for shipment, based on route and load
* @param map: map used for route calculation
* @param routes: an array of routes
* @param trucks: an array of 3 trucks for consideration
* @param numTrucks: number of trucks available
* @param cargo - ShipmentDetails struct, containing the shipment details
* @returns: the index of the best truck, or -1 if no truck is available
*/
int findTruck4Shipment(const struct Map* map, const struct Route* routes, struct Truck* trucks, int numTrucks, const struct ShipmentDetails* cargo);

///**
//* function to check if the shipping destination is on one of the routes, if yes, no diversion needed
//* @param route: the route to be compared 
//* @param point: destination point for delivery
//* @returns: true if point is on the route & no diversion needed; false if diversion is needed
//*/
//bool noDiversion(const struct Route* route, const struct Point* point);

/**
* if diversion path is needed for a shipment, display the path
* @param map: map used for route calculation, including buildings and obstacles
* @param route: find the best route to the destination
* @param destination: destination point for delivery
*/
void displayDiversion(const struct Map* map, const struct Route* route, const struct Point* destination);

#endif // !DELIVER_H_
