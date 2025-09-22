#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "deliver.h"
#include "datastruct.h"
#include "mapping.h"
#include <string.h>


int validateOrder(const struct Package* package, const struct Point* destination)
{
    if (package->size != 2 && package->size != 0.5 && package->size != 5)
    {
        //printf("Invalid size\n");
        return 0;
    }
    else if (package->weight > MAX_WEIGHT) {
        //printf("Invalid weight (must be 1-5000 kg .)\n");
        return 0;
    }
    else if (destination->col < 0 || destination->col > 24    || destination->row < 1 || destination->row > 25 ) {
        //printf("Invalid destination\n");
        return 0;
    }
    return 1;
}

int selectTrack(const struct Truck* t1, const struct Truck* t2)
{

    if ((t1->availableW == 0 || t1->availableV == 0) &&
        (t2->availableW == 0 || t2->availableV == 0)) {
        //printf("Both trucks are full\n");
        return 0;
    }
    if (t1->availableW == 0 || t1->availableV == 0) {
        if (t2->availableW > 0 && t2->availableV > 0) {
           // printf("First truck cannot load, select second truck\n");
            return 2;
        }
    }
    if (t2->availableW == 0 || t2->availableV == 0) {
        if (t1->availableW > 0 && t1->availableV > 0) {
           // printf("Second truck cannot load, select first truck\n");
            return 1;
        }
    }

    float remainWeight_t1, remainVolume_t1, remainWeight_t2, remainVolume_t2;

    remainWeight_t1 = t1->availableW / MAX_WEIGHT * 100;
    remainVolume_t1 = t1->availableV / MAX_VOLUME * 100;
    remainWeight_t2 = t2->availableW / MAX_WEIGHT * 100;
    remainVolume_t2 = t2->availableV / MAX_VOLUME * 100;

    float gapWeight = remainWeight_t1 - remainWeight_t2;
    float gapVolume = remainVolume_t1 - remainVolume_t2;

    if (gapVolume == 0)
    {
        if (gapWeight == 0)
        {
           // printf("same weight, volume\n return 0\n");
            return 0;
        }
        else if (gapWeight > 0) {
          //  printf("Selected first parameter truck\n return 1\n reason:more weight\n");
            return 1;
        }
        else {
          //  printf("Selected second parameter truck\n return 2\n reason:more weight\n");
            return 2;
        }
    }
    else if (gapVolume > 0) {
       // printf("Selected first parameter truck\n return 1\n reason:more volume\n");
        return 1;
    }
    else {
      //  printf("Selected second parameter truck\n return 2\n reason:more volume\n");
        return 2;
    }
  //  printf("other");
    return 0;
}

bool addPackageToTruck(struct Truck* truck, const struct Package* package)
{
    // Check if there's sufficient capacity 
    if (package->weight > truck->availableW || package->size > truck->availableV || truck->numPackages >= MAX_PACKAGES) {
        return false;
    }

    // Add package to truck 
    truck->packages[truck->numPackages] = *package;
    truck->numPackages++;
    // Update available capacity 
    truck->availableW -= package->weight;
    truck->availableV -= package->size;

    return true;
}

void initializeTruck(struct Truck* truck, const char* color)
{
    strcpy(truck->color, color);
    truck->numPackages = 0;
    truck->availableW = MAX_WEIGHT;  // Initialize with max capacity 
    truck->availableV = MAX_VOLUME;  // Initialize with max volume 
}

//new functions added for integration 
int getUserInput(struct ShipmentDetails* cargo) {
    printf("Enter shipment weight, box size and destination (0 0 x to stop): ");

    float w, s;
    int r;
    char c;
    int result = scanf("%f %f %d ", &w, &s, &r);
    int resultChar = scanf(" %c", &c);
    
    //clear remaining char in the input buffer
    int character;
    while ((character = getchar()) != '\n' && character != EOF);

    //check if it's stop condition
    if (w == 0 && s == 0 && c == 'x')
    {
        printf("Thanks for shipping with Seneca Polytechnic!\n");
        return 0;
    }
 
    struct Package tempP = { s, w };
    struct Point tempPoint = { r, c - 'A' }; //covert col letter to index, e.g. A=0, B=1, C=2...
    if (validateOrder(&tempP, &tempPoint)) {
            cargo->package = tempP;
            cargo->destination = tempPoint;
            return 1;
    }
   
    return -1;
}

int findTruck4Shipment(const struct Map* map, const struct Route* routes, struct Truck* trucks, int numTrucks, const struct ShipmentDetails* cargo) 
{

    //arrays to store the closest point index and distrance of each truck
    int closestPointIndex[3];
    double minDistance[3];

    //using provided functions "getClosestPoint()"& "distance()" to find closest point to the destination, on each route
    for (int i = 0; i < numTrucks; i++)
    {
        closestPointIndex[i] = getClosestPoint(&routes[i], cargo->destination);
        if (closestPointIndex[i] >= 0)
        {
            minDistance[i] = distance(&routes[i].points[closestPointIndex[i]], &cargo->destination);
        }
        else //can't find valid point
        {
            minDistance[i] = 9999999.0;
        }
    };

    //find best truck
    int bestTruckIndex = -1;
    double shortestDistance = 9999999.0;
    for (int i = 0; i < numTrucks; i++)
    {
        //check if the each truck has capacity to deliver
        if (trucks[i].availableW >= cargo->package.weight && trucks[i].availableV >= cargo->package.size)
        {
            //check if it's the closest truck to the destination
            if (minDistance[i] < shortestDistance)
            {
                shortestDistance = minDistance[i];
                bestTruckIndex = i;
            }
        }

    };
    if (bestTruckIndex != -1)
    {
        return bestTruckIndex;
    }

    return -1;
};

//bool noDiversion(const struct Route* route, const struct Point* point) {
//
//    //Adjust for zero-based indexing
//    struct Point adjustedP = { point->row - 1, point->col }; 
//    for (int i = 0; i < route->numPoints; i++)
//    {
//    struct Point adjustedP = { point->row - 1, point->col }; 
//        if (eqPt(route->points[i], adjustedP)) {
//            //using provided function "eqPt()" to check if the point is on the route
//            return true;
//        }
//    };
//    return false;
//};

void displayDiversion(const struct Map* map, const struct Route* route, const struct Point* destination){
  

    //find the closest point on the route to the destination
    int closestPointIndex= getClosestPoint(route, *destination);
    
    if (closestPointIndex >= 0) {
        struct Point closestPoint = route->points[closestPointIndex];

        struct Route diversionPath = shortestPath(map, closestPoint, *destination);
        if (diversionPath.numPoints == 0)//if shortestPath returns 0, means no diversion needed 
        {
            printf("no diversion\n");
        }
        else
        {
            printf("divert:");
            for (int i = 0; i < diversionPath.numPoints; i++) {
                //if (i > 0) printf(",");
                printf(" %d%c", diversionPath.points[i].row + 1, 'A' + diversionPath.points[i].col);
                if (i < diversionPath.numPoints - 1) printf(",");
            }
            printf("\n");
        }
 
    }
    else {
        printf("no diversion\n");
    }
}




