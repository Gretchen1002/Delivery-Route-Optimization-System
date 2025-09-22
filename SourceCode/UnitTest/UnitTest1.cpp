#define _CRT_SECURE_NO_WARNINGS
#define __STDC_WANT_LIB_EXT1__ 1
#include "pch.h"
#include "CppUnitTest.h"
#include "mapping_r.h"
#include "dataStruct_r.h"
#include "deliver_r.h"
#include <stdio.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	// Acceptance test 1 
	TEST_CLASS(ACCEPTANCE_1_maxWeightOnTruck) {
public:
	struct Map baseMap = populateMap();
	struct Route blueRoute = getBlueRoute();
	struct Route greenRoute = getGreenRoute();
	struct Route yellowRoute = getYellowRoute();
	struct Route routes[3] = { blueRoute, greenRoute, yellowRoute };
	TEST_METHOD(allEnoughCapacity) {
		struct ShipmentDetails cargo = { {2,500}, {6,0} };
		struct Truck truckBlue = { "blue", {0}, 1, 5000.0, 250.0 };
		struct Truck truckGreen = { "green", {0}, 1, 5000.0, 250.0 };
		struct Truck truckYellow = { "yellow", {0}, 1, 5000.0, 250.0 };
		struct Truck trucks[] = { truckBlue, truckGreen,truckYellow };
		int result = findTruck4Shipment(&baseMap, routes, trucks, 3, &cargo);
		Assert::AreEqual(0, result); //Return first index truck
	}
	TEST_METHOD(truck1exceedingMaximumWeightCapacity) {
		struct ShipmentDetails cargo = { {2,1500}, {6,0} };
		struct Truck truckBlue = { "blue", {0}, 1, 1000.0, 250.0 };
		struct Truck truckGreen = { "green", {0}, 1, 5000.0, 250.0 };
		struct Truck truckYellow = { "yellow", {0}, 1, 5000.0, 250.0 };
		struct Truck trucks[] = { truckBlue, truckGreen,truckYellow };
		int result = findTruck4Shipment(&baseMap, routes, trucks, 3, &cargo);
		Assert::AreEqual(1, result); //Blue over capacity, select green
	}
	TEST_METHOD(truck1and2exceedingMaximumWeightCapacity) {
		struct ShipmentDetails cargo = { {2,1500}, {6,0} };
		struct Truck truckBlue = { "blue", {0}, 1, 1000.0, 250.0 };
		struct Truck truckGreen = { "green", {0}, 1, 1000.0, 250.0 };
		struct Truck truckYellow = { "yellow", {0}, 1, 5000.0, 250.0 };
		struct Truck trucks[] = { truckBlue, truckGreen,truckYellow };
		int result = findTruck4Shipment(&baseMap, routes, trucks, 3, &cargo);
		Assert::AreEqual(2, result); //Blue & Green over capacity, select yellow
	}
	TEST_METHOD(allTruckexceedingMaximumWeightCapacity) {
		struct ShipmentDetails cargo = { {2,1500}, {6,0} };
		struct Truck truckBlue = { "blue", {0}, 1, 1000.0, 250.0 };
		struct Truck truckGreen = { "green", {0}, 1, 1000.0, 250.0 };
		struct Truck truckYellow = { "yellow", {0}, 1, 1000.0, 250.0 };
		struct Truck trucks[] = { truckBlue, truckGreen,truckYellow };
		int result = findTruck4Shipment(&baseMap, routes, trucks, 3, &cargo);
		Assert::AreEqual(-1, result, L"There is no avaliable truck, will be shipped tomorrow");
	}

	};

	// Acceptance test 2
	TEST_CLASS(ACCEPTANCE_2_maxVolumeOnTruck) {
public:
	struct Map baseMap = populateMap();
	struct Route blueRoute = getBlueRoute();
	struct Route greenRoute = getGreenRoute();
	struct Route yellowRoute = getYellowRoute();
	struct Route routes[3] = { blueRoute, greenRoute, yellowRoute };

	TEST_METHOD(allEnoughCapacity) {
		struct ShipmentDetails cargo = { {5,50}, {6,0} };
		struct Truck truckBlue = { "blue", {0}, 1, 4000.0, 250.0 };
		struct Truck truckGreen = { "green", {0}, 1, 4000.0, 250.0 };
		struct Truck truckYellow = { "yellow", {0}, 1, 4000.0, 250.0 };
		struct Truck trucks[] = { truckBlue, truckGreen,truckYellow };
		int result = findTruck4Shipment(&baseMap, routes, trucks, 3, &cargo);
		Assert::AreEqual(0, result);
	}
	TEST_METHOD(truck1exceedingMaximumVolumeCapacity) {
		struct ShipmentDetails cargo = { {5,50}, {6,0} };
		struct Truck truckBlue = { "blue", {0}, 1, 4000.0, 0.0 };
		struct Truck truckGreen = { "green", {0}, 1, 4000.0, 250.0 };
		struct Truck truckYellow = { "yellow", {0}, 1, 4000.0, 250.0 };
		struct Truck trucks[] = { truckBlue, truckGreen,truckYellow };
		int result = findTruck4Shipment(&baseMap, routes, trucks, 3, &cargo);
		Assert::AreEqual(1, result);
	}
	TEST_METHOD(truck1and2exceedingMaximumVolumeCapacity) {
		struct ShipmentDetails cargo = { {5,50}, {6,0} };
		struct Truck truckBlue = { "blue", {0}, 1, 4000.0, 0.0 };
		struct Truck truckGreen = { "green", {0}, 1, 4000.0, 0.0 };
		struct Truck truckYellow = { "yellow", {0}, 1, 4000.0, 250.0 };
		struct Truck trucks[] = { truckBlue, truckGreen,truckYellow };
		int result = findTruck4Shipment(&baseMap, routes, trucks, 3, &cargo);
		Assert::AreEqual(2, result);
	}
	TEST_METHOD(allTruckexceedingMaximumWeightCapacity) {
		struct ShipmentDetails cargo = { {5,50}, {6,0} };
		struct Truck truckBlue = { "blue", {0}, 1, 4000.0, 0.0 };
		struct Truck truckGreen = { "green", {0}, 1, 4000.0, 0.0 };
		struct Truck truckYellow = { "yellow", {0}, 1, 4000.0, 0.0 };
		struct Truck trucks[] = { truckBlue, truckGreen,truckYellow };
		int result = findTruck4Shipment(&baseMap, routes, trucks, 3, &cargo);
		Assert::AreEqual(-1, result, L"There is no avaliable truck, will be shipped tomorrow");
	}

	};

	// Acceptance test 3
	TEST_CLASS(ACCEPTANCE_3_validPackageSize) {
public:
	struct ShipmentDetails cargo = { 0 };
	FILE* stream;

	TEST_METHOD(validPackageSize) {
		if (freopen_s(&stream, "C:\\Users\\user\\source\\repos\\SFT 221\\SFT MS04\\Unit Test\\test_input.txt", "r", stdin) != 0) {
			perror("Error opening file");
			Assert::Fail(L"Failed to open input file");
		}
		int result = getUserInput(&cargo); //20 2 7 A
		fclose(stream);
		Assert::AreEqual(1, result);
	}
	TEST_METHOD(validPacageSize2) {
		cargo = { 0 };
		if (freopen_s(&stream, "C:\\Users\\user\\source\\repos\\SFT 221\\SFT MS04\\Unit Test\\test_input.txt", "r", stdin) != 0) {
			perror("Error opening file");
			Assert::Fail(L"Failed to open input file");
		}
		char buffer[256];
		if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
			perror("Error reading first line");
			fclose(stream);
			Assert::Fail(L"Failed to read first line");
		}
		int result = getUserInput(&cargo); //0 0 x
		fclose(stream);
		Assert::AreEqual(1, result);
	}
	TEST_METHOD(validateOverPackageSize) {
		cargo = { 0 };
		if (freopen_s(&stream, "C:\\Users\\user\\source\\repos\\SFT 221\\SFT MS04\\Unit Test\\test_input.txt", "r", stdin) != 0) {
			perror("Error opening file");
			Assert::Fail(L"Failed to open input file");
		}
		// Skip the first two lines
		char buffer[256];
		for (int i = 0; i < 2; i++) {
			if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
				perror("Error reading line");
				fclose(stream);
				Assert::Fail(L"Failed to read line");
			}
		}
		int result = getUserInput(&cargo); //20 10 7 A
		fclose(stream);
		Assert::AreEqual(-1, result);
	}
	TEST_METHOD(zeroInput) {
		cargo = { 0 };
		if (freopen_s(&stream, "C:\\Users\\user\\source\\repos\\SFT 221\\SFT MS04\\Unit Test\\test_input.txt", "r", stdin) != 0) {
			perror("Error opening file");
			Assert::Fail(L"Failed to open input file");
		}

		// Skip the first three lines
		char buffer[256];
		for (int i = 0; i < 3; i++) {
			if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
				perror("Error reading line");
				fclose(stream);
				Assert::Fail(L"Failed to read line");
			}
		}
		int result = getUserInput(&cargo);
		fclose(stream);
		Assert::AreEqual(0, result);
	}
	};

	// Acceptance test 4
	TEST_CLASS(ACCEPTANCE_4_validDestinationPoint) {
public:
	struct ShipmentDetails cargo = { 0 };
	FILE* stream;
	TEST_METHOD(validDestination) {
		//findTruck4Shipment;
		if (freopen_s(&stream, "C:\\Users\\user\\source\\repos\\SFT 221\\SFT MS04\\Unit Test\\test_input2.txt", "r", stdin) != 0) {
			perror("Error opening file");
			Assert::Fail(L"Failed to open input file");
		}
		int result = getUserInput(&cargo); //20 5 7 A
		fclose(stream);
		Assert::AreEqual(1, result);
	}
	TEST_METHOD(validDestinationEdgecase) {
		cargo = { 0 };
		if (freopen_s(&stream, "C:\\Users\\user\\source\\repos\\SFT 221\\SFT MS04\\Unit Test\\test_input2.txt", "r", stdin) != 0) {
			perror("Error opening file");
			Assert::Fail(L"Failed to open input file");
		}
		char buffer[256];
		if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
			perror("Error reading first line");
			fclose(stream);
			Assert::Fail(L"Failed to read first line");
		}
		int result = getUserInput(&cargo); //20 5 25 Y
		fclose(stream);
		Assert::AreEqual(1, result);
	}
	TEST_METHOD(validDestinationNoExist) {
		cargo = { 0 };
		if (freopen_s(&stream, "C:\\Users\\user\\source\\repos\\SFT 221\\SFT MS04\\Unit Test\\test_input2.txt", "r", stdin) != 0) {
			perror("Error opening file");
			Assert::Fail(L"Failed to open input file");
		}
		// Skip the first two lines
		char buffer[256];
		for (int i = 0; i < 2; i++) {
			if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
				perror("Error reading line");
				fclose(stream);
				Assert::Fail(L"Failed to read line");
			}
		}
		int result = getUserInput(&cargo); //20 5 28 M
		fclose(stream);
		Assert::AreEqual(-1, result);
	}
	TEST_METHOD(validDestinationUnexpectedInput) {
		cargo = { 0 };
		if (freopen_s(&stream, "C:\\Users\\user\\source\\repos\\SFT 221\\SFT MS04\\Unit Test\\test_input2.txt", "r", stdin) != 0) {
			perror("Error opening file");
			Assert::Fail(L"Failed to open input file");
		}

		// Skip the first three lines
		char buffer[256];
		for (int i = 0; i < 3; i++) {
			if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
				perror("Error reading line");
				fclose(stream);
				Assert::Fail(L"Failed to read line");
			}
		}
		int result = getUserInput(&cargo);
		fclose(stream);
		Assert::AreEqual(-1, result);
	}
	};

	TEST_CLASS(ACCEPTANCE_5_getTheShortestPath) {
public:
	struct Map baseMap = populateMap();
	struct Route blueRoute = getBlueRoute();
	struct Route greenRoute = getGreenRoute();
	struct Route yellowRoute = getYellowRoute();
	struct Route routes[3] = { blueRoute, greenRoute, yellowRoute };
	struct Map routeMap = addRoute(&baseMap, &blueRoute);
	FILE* stream;

	TEST_METHOD(findShortestPath1) {
		struct ShipmentDetails cargo = { {0,0}, {6,0} };
		if (freopen_s(&stream, "C:\\Users\\user\\source\\repos\\SFT 221\\SFT MS04\\Unit Test\\test_output.txt", "wb", stdout) != 0) {
			perror("Error opening file");
			Assert::Fail(L"Failed to open input file");
		}
		displayDiversion(&routeMap, &routes[0], &cargo.destination);
		fclose(stdout);
		freopen_s(&stream, "C:\\Users\\user\\source\\repos\\SFT 221\\SFT MS04\\Unit Test\\test_output.txt", "r", stdin);
		char buffer[256];
		if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
			perror("Error reading first line");
			fclose(stream);
			Assert::Fail(L"Failed to read first line");
		}
		Assert::AreEqual("divert: 5A, 6A, 7A\n", buffer);
		fclose(stream);
	}

	TEST_METHOD(findShortestPath2) {
		routeMap = addRoute(&routeMap, &greenRoute);
		struct ShipmentDetails cargo = { {0,0}, {5,25} }; //8Y
		if (freopen_s(&stream, "C:\\Users\\user\\source\\repos\\SFT 221\\SFT MS04\\Unit Test\\test_output2.txt", "wb", stdout) != 0) {
			perror("Error opening file");
			Assert::Fail(L"Failed to open input file");
		}
		displayDiversion(&routeMap, &routes[1], &cargo.destination);
		fclose(stdout);
		freopen_s(&stream, "C:\\Users\\user\\source\\repos\\SFT 221\\SFT MS04\\Unit Test\\test_output2.txt", "r", stdin);
		char buffer[256];
		if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
			perror("Error reading first line");
			fclose(stream);
			Assert::Fail(L"Failed to read first line");
		}
		Assert::AreEqual("divert: 5A, 5B, 5C, 5D, 5E, 5F, 5G, 5H, 5I, 5J, 5K, 5L, 5M, 5N, 5O, 5P, 5Q, 5R, 5S, 5T, 5U, 5V, 5W, 5X, 6Y, 6Z\n", buffer);
		fclose(stream);
	}

	TEST_METHOD(findShortestPath3) {
		routeMap = addRoute(&routeMap, &yellowRoute);
		struct ShipmentDetails cargo = { {0,0}, {12,3} };
		if (freopen_s(&stream, "C:\\Users\\user\\source\\repos\\SFT 221\\SFT MS04\\Unit Test\\test_output3.txt", "wb", stdout) != 0) {
			perror("Error opening file");
			Assert::Fail(L"Failed to open input file");
		}
		displayDiversion(&routeMap, &routes[2], &cargo.destination);
		fclose(stdout);
		freopen_s(&stream, "C:\\Users\\user\\source\\repos\\SFT 221\\SFT MS04\\Unit Test\\test_output3.txt", "r", stdin);
		char buffer[256];
		if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
			perror("Error reading first line");
			fclose(stream);
			Assert::Fail(L"Failed to read first line");
		}
		Assert::AreEqual("divert: 5A, 5B, 6C, 7C, 8C, 9C, 10C, 11B, 12B, 13B, 13C, 13D\n", buffer);
		fclose(stream);
	}

	TEST_METHOD(findShortestPath4) {
		routeMap = addRoute(&routeMap, &yellowRoute);
		struct ShipmentDetails cargo = { {0,0}, {25,25} };
		if (freopen_s(&stream, "C:\\Users\\user\\source\\repos\\SFT 221\\SFT MS04\\Unit Test\\test_output4.txt", "wb", stdout) != 0) {
			perror("Error opening file");
			Assert::Fail(L"Failed to open input file");
		}
		displayDiversion(&routeMap, &routes[2], &cargo.destination);
		fclose(stdout);
		freopen_s(&stream, "C:\\Users\\user\\source\\repos\\SFT 221\\SFT MS04\\Unit Test\\test_output4.txt", "r", stdin);
		char buffer[256];
		if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
			perror("Error reading first line");
			fclose(stream);
			Assert::Fail(L"Failed to read first line");
		}
		Assert::AreEqual("Cannot reach destination from this route\n", buffer);
		fclose(stream);
	}
	};

	// Acceptance Tests
	TEST_CLASS(AcceptanceTests6to9) {
public:

	TEST_METHOD(R006_GetClosestPoint) {
		// Create a route with multiple points
		struct Point p1 = { 5, 'A' };  // Starting point
		struct Point p2 = { 5, 'M' };  // Middle point
		struct Point p3 = { 5, 'Y' };  // End point
		struct Route route = { { p1, p2, p3 }, 3, BLUE };

		// Test point to find closest match
		struct Point target = { 5, 'N' };  // Should be closest to p2

		// Find the closest point on route
		int closestIndex = getClosestPoint(&route, target);

		Assert::AreEqual(1, closestIndex);
	}


	TEST_METHOD(R007_GetBestTruck) {
		struct Truck t1 = { "blue", {0}, 0, 4000.0, 200.0 };   // 80% weight, 80% volume
		struct Truck t2 = { "green", {0}, 0, 3000.0, 150.0 };  // 60% weight, 60% volume

		// Select the best truck based on remaining capacity percentage
		int selection = selectTrack(&t1, &t2);

		// Verify selection,should choose t1
		Assert::AreEqual(1, selection);
	}


	TEST_METHOD(R008_GetDistanceBetweenPoints) {
		// Create two points with known distance
		struct Point p1 = { 1, 'A' };
		struct Point p2 = { 1, 'C' }; // 2 units away horizontally

		// Calculate distance between points
		double dist = distance(&p1, &p2);

		// should be 2 unit
		Assert::AreEqual(2.0, dist);
	}


	TEST_METHOD(R009_DetermineDiversionPath) {

		//struct Map map = populateMap();
		//struct Route blueRoute = getBlueRoute();
		//struct Point destination = { 10, 15 };  // Point not on route

		//// Add route to map and test diversion
		//struct Map routeMap = addRoute(&map, &blueRoute);
		//displayDiversion(&routeMap, &blueRoute, &destination);

		//// Verify path can be found
		//struct Route path = shortestPath(&map, blueRoute.points[0], destination);
		//Assert::IsTrue(path.numPoints > 0);
	}
	};

	//black box test 1
	TEST_CLASS(equalPoint)
	{
	public:

		TEST_METHOD(isValidTest1)
		{
			Point P1, P2;
			P1.row = 5;
			P1.col = 'A';
			P2.row = 5;
			P2.col = 'J';
			Assert::IsFalse(eqPt(P1, P2));
		};
		TEST_METHOD(isValidTest2)
		{
			Point P1, P2;
			P1.row = 1;
			P1.col = 'p';
			P2.row = 20;
			P2.col = 'p';
			Assert::IsFalse(eqPt(P1, P2));
		};
		TEST_METHOD(isValidTest3)
		{
			Point P1, P2;
			P1.row = 1;
			P1.col = 'A';
			P2.row = 1;
			P2.col = 'A';
			Assert::IsTrue(eqPt(P1, P2));
		};
		TEST_METHOD(upperLowerTest)
		{
			Point P1, P2;
			P1.row = 20;
			P1.col = 'G';
			P2.row = 20;
			P2.col = 'g';
			Assert::IsFalse(eqPt(P1, P2));
		};
	};

	//black box test 2
	TEST_CLASS(distanceTest)
	{
	public:

		TEST_METHOD(TestSamePoint)
		{
			struct Point p1 = { 6, 'M' };
			struct Point p2 = { 6, 'M' };

			double result = distance(&p1, &p2);
			Assert::AreEqual(0.0, result, L"Distance between same point should be 0");
		}

		TEST_METHOD(TestMaxDiagonalDistance)
		{
			struct Point p1 = { 1, 'A' };
			struct Point p2 = { 25, 'Y' };

			double result = distance(&p1, &p2);
			Assert::AreEqual(33.941, result, 0.01, L"Distance between two diagonal points should match expected result");
		}

		TEST_METHOD(TestSameRow)
		{
			struct Point p1 = { 10, 'E' };
			struct Point p2 = { 10, 'O' };

			double result = distance(&p1, &p2);
			Assert::AreEqual(10.0, result, 0.01, L"Distance on the same row should be correct");
		}

		TEST_METHOD(TestThroughBlockedArea)
		{
			struct Point p1 = { 8, 'P' };
			struct Point p2 = { 20, 'F' };

			double result = distance(&p1, &p2);
			Assert::AreEqual(15.62, result, 0.01, L"Distance through a blocked area should match expected result");
		}
	};

	//black box test 3
	TEST_CLASS(initializeTruckTest)
	{
	public:


		TEST_METHOD(TestBlueTruck)
		{
			struct Truck truck;
			const char* color = "BLUE";

			initializeTruck(&truck, color);

			Assert::AreEqual("BLUE", truck.color);
			Assert::AreEqual(0, truck.numPackages);
			Assert::AreEqual((float)MAX_WEIGHT, truck.availableW);
			Assert::AreEqual((float)MAX_VOLUME, truck.availableV);
		}

		TEST_METHOD(TestGreenTruck)
		{
			struct Truck truck;
			const char* color = "GREEN";

			initializeTruck(&truck, color);

			Assert::AreEqual("GREEN", truck.color);
			Assert::AreEqual(0, truck.numPackages);
			Assert::AreEqual((float)MAX_WEIGHT, truck.availableW);
			Assert::AreEqual((float)MAX_VOLUME, truck.availableV);
		}

		TEST_METHOD(TestYellowTruck)
		{
			struct Truck truck;
			const char* color = "YELLOW";

			initializeTruck(&truck, color);

			Assert::AreEqual("YELLOW", truck.color);
			Assert::AreEqual(0, truck.numPackages);
			Assert::AreEqual((float)MAX_WEIGHT, truck.availableW);
			Assert::AreEqual((float)MAX_VOLUME, truck.availableV);
		}

		TEST_METHOD(TestTruck_EmptyString)
		{
			struct Truck truck;
			const char* color = "";

			initializeTruck(&truck, color);

			Assert::AreEqual("", truck.color);
			Assert::AreEqual(0, truck.numPackages);
			Assert::AreEqual((float)MAX_WEIGHT, truck.availableW);
			Assert::AreEqual((float)MAX_VOLUME, truck.availableV);
		}
	};

	//black box test 4
	TEST_CLASS(addPackageToTruckTest)
	{
	public:
		TEST_METHOD(validTest)
		{
			struct Truck truck;
			initializeTruck(&truck, "BLUE");

			struct Package package;
			package.weight = 100.0;
			package.size = 2.0;

			bool result = addPackageToTruck(&truck, &package);

			Assert::IsTrue(result);
			Assert::AreEqual(1, truck.numPackages);
			Assert::AreEqual(MAX_WEIGHT - 100.0f, truck.availableW);
			Assert::AreEqual(MAX_VOLUME - 2.0f, truck.availableV);
			Assert::AreEqual(100.0f, truck.packages[0].weight);
			Assert::AreEqual(2.0f, truck.packages[0].size);
		}

		TEST_METHOD(overweightTest)
		{
			struct Truck truck;
			initializeTruck(&truck, "BLUE");

			struct Package package;
			package.weight = MAX_WEIGHT + 1.0f;
			package.size = 2.0;

			bool result = addPackageToTruck(&truck, &package);

			Assert::IsFalse(result);
			Assert::AreEqual(0, truck.numPackages);
			Assert::AreEqual((float)MAX_WEIGHT, truck.availableW);
			Assert::AreEqual((float)MAX_VOLUME, truck.availableV);
		}

		TEST_METHOD(volumeFailedTest)
		{
			struct Truck truck;
			initializeTruck(&truck, "BLUE");

			struct Package package;
			package.weight = 100.0;
			package.size = MAX_VOLUME + 1.0;

			bool result = addPackageToTruck(&truck, &package);

			Assert::IsFalse(result);
			Assert::AreEqual(0, truck.numPackages);
			Assert::AreEqual((float)MAX_WEIGHT, truck.availableW);
			Assert::AreEqual((float)MAX_VOLUME, truck.availableV);
		}

		TEST_METHOD(multiplePackTest)
		{
			struct Truck truck;
			initializeTruck(&truck, "BLUE");

			struct Package package1;
			package1.weight = 1000.0;
			package1.size = 50.0;

			struct Package package2;
			package2.weight = 2000.0;
			package2.size = 100.0;

			bool result1 = addPackageToTruck(&truck, &package1);
			bool result2 = addPackageToTruck(&truck, &package2);

			Assert::IsTrue(result1);
			Assert::IsTrue(result2);
			Assert::AreEqual(2, truck.numPackages);
			Assert::AreEqual(MAX_WEIGHT - 3000.0f, truck.availableW);
			Assert::AreEqual(MAX_VOLUME - 150.0f, truck.availableV);
			Assert::AreEqual(1000.0f, truck.packages[0].weight);
			Assert::AreEqual(50.0f, truck.packages[0].size);
			Assert::AreEqual(2000.0f, truck.packages[1].weight);
			Assert::AreEqual(100.0f, truck.packages[1].size);
		}
	};

	//black box test 5
	TEST_CLASS(ValidateOrderTest)
	{
	public:

		TEST_METHOD(TestValidPackageAndReachableDestination)
		{
			struct Package package = { 2.0, 50.0 };
			struct Point destination = { 6, 13 }; //6M

			int result = validateOrder(&package, &destination);

			Assert::AreEqual(1, result, L"Valid package and reachable destination should return 1");
		}

		TEST_METHOD(TestPackageExceedsMaximumSizeAndWeight)
		{
			struct Package package = { 3.0, 6000.0 };
			struct Point destination = { 6, 13 }; //6M

			int result = validateOrder(&package, &destination);

			Assert::AreEqual(0, result, L"Package exceeding max size and weight should return 0");
		}

		TEST_METHOD(TestUnreachableDestination)
		{
			struct Package package = { 2.0, 50.0 };
			struct Point destination = { 26, 26 }; //26Z

			int result = validateOrder(&package, &destination);

			Assert::AreEqual(0, result, L"Unreachable destination should return 0");
		}

		TEST_METHOD(TestEdgeCaseMaximumAllowedWeight)
		{
			struct Package package = { 5.0, 5000.0 };
			struct Point destination = { 6, 13 }; //6M

			int result = validateOrder(&package, &destination);

			Assert::AreEqual(1, result, L"Edge case with max allowed weight should return 1");
		}
	};

	//black box test 6
	TEST_CLASS(SelectTrackTest)
	{
	public:
		TEST_METHOD(TestBothTrucksSameCapacity) //Haruna changed
		{
			struct Truck t1 = { "", { 0 }, 0, 3000, 150 };
			struct Truck t2 = { "", { 0 }, 0, 3000, 150 };
			int result = selectTrack(&t1, &t2);
			Assert::AreEqual(0, result, L"Both trucks have the same available weight and volume.");
		}

		TEST_METHOD(TestTruck1MoreAvailableVolume)
		{
			struct Truck t1 = { "", { 0 }, 0, 3000, 200 };
			struct Truck t2 = { "", { 0 }, 0, 3000, 150 };
			int result = selectTrack(&t1, &t2);
			Assert::AreEqual(1, result, L"Truck 1 should be selected due to higher volume.");
		}

		TEST_METHOD(TestTruck2MoreAvailableWeight)
		{
			struct Truck t1 = { "", { 0 }, 0, 2000, 150 };
			struct Truck t2 = { "", { 0 }, 0, 4000, 150 };
			int result = selectTrack(&t1, &t2);
			Assert::AreEqual(2, result, L"Truck 2 should be selected due to higher weight.");
		}

		TEST_METHOD(TestBothTrucksZeroCapacity)
		{
			struct Truck t1 = { "", { 0 }, 0, 0, 150 };
			struct Truck t2 = { "", { 0 }, 0, 3000, 0 };
			int result = selectTrack(&t1, &t2);
			Assert::AreEqual(0, result, L"Both trucks are full");
		}
	};

	//White box test comment: use the version --#define MAX_WEIGHT 5000 : MAX_VOLUME 250 : MAX_PACKAGES 500
	// White box test 1
	TEST_CLASS(getClosetPointTest) {
public:
	TEST_METHOD(isValideTest1) {
		struct Point p1 = { 0,0 };
		struct Point p2 = { 4, 9 }; //5J
		struct Point p3 = { 4,3 }; //5D
		struct Route r1 = { { p1,p2,p3 }, 3, DIVERSION };
		struct Point d1 = { 2, 10 }; // 3K
		int result = getClosestPoint(&r1, d1);
		Assert::AreEqual(1, result);
	}

	TEST_METHOD(sameDistance) {
		struct Point p1 = { 9,'V' };
		struct Point p2 = { 9,'W' };
		struct Point p3 = { 17,'V' };
		struct Point p4 = { 17,'W' };
		struct Route r1 = { { p1,p2,p3,p4 }, 4, DIVERSION };
		struct Point d1 = { 13, 'V' };
		int result = getClosestPoint(&r1, d1);
		Assert::AreEqual(0, result);
	}

	TEST_METHOD(noRoadData) {
		struct Route r1 = { {0}, 0, DIVERSION };
		struct Point d1 = { 13, 'V' };
		int result = getClosestPoint(&r1, d1);
		Assert::AreEqual(-1, result);
	}

	TEST_METHOD(invalidDestination) {
		struct Map baseMap = populateMap();
		struct Route blueRoute = getBlueRoute();
		struct Map routeMap = addRoute(&baseMap, &blueRoute);

		struct Point p1 = { 24,'Y' };
		struct Point p2 = { 24, 'Z' };
		struct Route r1 = { { p1,p2 }, 2, DIVERSION };
		struct Point d1 = { 23, 'Z' };
		int result = getClosestPoint(&r1, d1);
		Assert::AreEqual(1, result);
	}
	};

	// White box test 2
	TEST_CLASS(validateOrderTest) {
public:
	TEST_METHOD(validateClear) {
		struct Package p1 = { 2.0, 400.0 };
		struct Point d1 = { 12, 12 }; //12L
		int result = validateOrder(&p1, &d1);
		Assert::AreEqual(1, result);
	}

	TEST_METHOD(validateDestination) {
		struct Package p1 = { 2.0, 400.0 };
		struct Point d1 = { 28, 24 }; //28X
		int result = validateOrder(&p1, &d1);
		Assert::AreEqual(0, result, L"Invalid destination");
	}

	TEST_METHOD(validateWeight) {
		struct Package p1 = { 2.0, 5500.0 };
		struct Point d1 = { 12, 12 }; //12L
		int result = validateOrder(&p1, &d1);
		Assert::AreEqual(0, result, L"Invalid weight (must be 1-5000 kg .)");
	}

	TEST_METHOD(validateSize) {
		struct Package p1 = { 10.0, 400.0 };
		struct Point d1 = { 12, 12 }; //12L
		int result = validateOrder(&p1, &d1);
		Assert::AreEqual(0, result, L"Invalid size");
	}
	};

	// White box test 3
	TEST_CLASS(selectTruckTest) {
public:
	TEST_METHOD(compareWeight) {
		struct Package p1 = { 40.0, 400.0 };
		struct Package p2 = { 40.0, 4000.0 };
		struct Truck t1 = { "blue",{p1},1,4600.0,210.0 };
		struct Truck t2 = { "green",{p2},1,1000.0,210.0 };
		int result = selectTrack(&t1, &t2);
		Assert::AreEqual(1, result);
	}

	TEST_METHOD(compareVolume) {
		struct Package p1 = { 250.0, 400.0 };
		struct Package p2 = { 40.0, 4000.0 };
		struct Truck t1 = { "blue",{p1},1,4600.0,0.0 };
		struct Truck t2 = { "green",{p2},1,1000.0,210.0 };
		int result = selectTrack(&t1, &t2);
		Assert::AreEqual(2, result);
	}

	TEST_METHOD(sameCase) { //Haruna changed
		struct Package p1 = { 40.0, 400.0 };
		struct Package p2 = { 40.0, 400.0 };
		struct Truck t1 = { "blue",{p1},1,4600.0,210.0 };
		struct Truck t2 = { "green",{p2},1,4600.0,210.0 };
		int result = selectTrack(&t1, &t2);
		Assert::AreEqual(0, result);
		// expected, actual
	}

	TEST_METHOD(bothFull) {
		struct Package p1 = { 250.0, 5000.0 };
		struct Package p2 = { 250.0, 5000.0 };
		struct Truck t1 = { "blue",{p1},1,0.0,0.0 };
		struct Truck t2 = { "green",{p2},1,0.0,0.0 };
		int result = selectTrack(&t1, &t2);
		Assert::AreEqual(0, result);
	}
	};

	//White box test comment: use the version --#define MAX_WEIGHT 5000 : MAX_VOLUME 250 : MAX_PACKAGES 500
	// White box test 4
	TEST_CLASS(addPackageToTruckTestDataCheck) {
public:
	TEST_METHOD(addToLargestAmount) {
		struct Package p1 = { 5.0, 10.0 };//Pacakge size only have 3 type: 1, 3, 5 cubic meters
		struct Truck t1 = { "blue",{p1},1,25.0,8.0 };
		struct Package p2 = { 3.0, 10.0 };
		bool result = addPackageToTruck(&t1, &p2);
		Assert::IsTrue(result);
	}

	TEST_METHOD(packageNumSuccessfulAdd) {
		struct Package p1 = { 40.0, 400.0 };
		struct Truck t1 = { "blue", {p1}, 1, 4600.0, 210.0 };
		struct Package p2 = { 5.0, 400.0 };
		bool result = addPackageToTruck(&t1, &p2);
		Assert::IsTrue(result);
		Assert::AreEqual(2, t1.numPackages);
	}
	TEST_METHOD(outOfRange) {
		struct Package p1 = { 40.0, 400.0 };
		struct Truck t1 = { "blue", {p1}, 1, 4600.0, 210.0 };
		struct Package p2 = { 5000.0, 200.0 };
		bool result = addPackageToTruck(&t1, &p2);
		Assert::IsFalse(result);
	}
	TEST_METHOD(outOfRange2) {
		struct Package p1 = { 40.0, 400.0 };
		struct Truck t1 = { "blue", {p1}, 1, 4600.0, 210.0 };
		struct Package p2 = { 3000.0, 300.0 };
		bool result = addPackageToTruck(&t1, &p2);
		Assert::IsFalse(result);
	}
	};

	// White box test 5
	TEST_CLASS(initializeTruckTestEdgeCheck) {
public:
	TEST_METHOD(fromEmpty) {
		struct Truck t1 = { "blue",{},0,0.0,0.0 };
		initializeTruck(&t1, "blue");
		Assert::AreEqual(0, t1.numPackages);
		Assert::AreEqual(5000.0f, t1.availableW);//Set to maximum weight capacity, and type is float
		Assert::AreEqual(250.0f, t1.availableV);// Set to maximum volume capacity
	}
	TEST_METHOD(colorChange) {
		struct Truck t1 = { "blue",{},0,0.0,0.0 };
		initializeTruck(&t1, "green");
		Assert::AreEqual(0, t1.numPackages);
		Assert::AreEqual(5000.0f, t1.availableW);
		Assert::AreEqual(250.0f, t1.availableV);
	}

	TEST_METHOD(fullCapacity) {
		struct Truck t1 = { "green", {}, 0, 5000.0, 250.0 };
		initializeTruck(&t1, "yellow");
		Assert::AreEqual(0, t1.numPackages);
		Assert::AreEqual(5000.0f, t1.availableW);
		Assert::AreEqual(250.0f, t1.availableV);
		//Assert::AreEqual(strcmp(t1.color, "yellow"), 0);
	}
	TEST_METHOD(colorVeryLong) {
		struct Truck t1 = { "blue", {}, 0, 0.0, 0.0 };
		char longColor[] = "this_is_a_very_long_color_name_exceeding_normal_length";
		initializeTruck(&t1, longColor);
		Assert::AreEqual(0, t1.numPackages);
		Assert::AreEqual(5000.0f, t1.availableW);
		Assert::AreEqual(250.0f, t1.availableV);
		//Assert::AreEqual(strcmp(t1.color, longColor), 0);
	}
	};

	// White box test 6
	TEST_CLASS(equalPointEdgeDataCheck) {
public:
	TEST_METHOD(colCaseDif) {
		Point P1, P2;
		P1.row = 13;
		P1.col = 'G';
		P2.row = 13;
		P2.col = 'g';
		Assert::IsFalse(eqPt(P1, P2)); // Same row, different case in column
	}
	TEST_METHOD(colAtstart) {
		Point P1, P2;
		P1.row = 0;
		P1.col = '\0';
		P2.row = 0;
		P2.col = '\0';
		Assert::IsTrue(eqPt(P1, P2)); // Edge case: both points are at the origin
	}
	TEST_METHOD(negativeRowValue) {
		Point P1, P2;
		P1.row = -1;
		P1.col = 'F';
		P2.row = -1;
		P2.col = 'F';
		Assert::IsTrue(eqPt(P1, P2));
	}
	TEST_METHOD(bigRowValue) {
		Point P1, P2;
		P1.row = 100000;
		P1.col = 'A';
		P2.row = 100000;
		P2.col = 'A';
		Assert::IsTrue(eqPt(P1, P2));
	}
	};

	// Integration test 1
	TEST_CLASS(addPackageAndselectTruck) {
public:
	TEST_METHOD(truck1Available) {
		struct Truck t1 = { "blue", {0}, 0, 5000.0, 250.0 };
		struct Package p1 = { 5.0, 1000.0 };
		struct Truck t2 = { "green", {0}, 0, 5000.0, 250.0 };
		struct Package p2 = { 5.0, 2000.0 };
		bool result = addPackageToTruck(&t1, &p1);
		bool result2 = addPackageToTruck(&t2, &p2);
		int result3 = selectTrack(&t1, &t2);
		Assert::AreEqual(1, result3);  //t1 has more weight capacity
	}
	TEST_METHOD(truck2Available) {
		struct Truck t1 = { "blue", {0}, 0, 5000.0, 250.0 }; //weight 20% volume 30%
		struct Package p1 = { 75.0, 1000.0 };
		struct Truck t2 = { "green", {0}, 0, 5000.0, 250.0 }; //weight 20% volume 2%
		struct Package p2 = { 5.0, 1000.0 };
		bool result = addPackageToTruck(&t1, &p1);
		bool result2 = addPackageToTruck(&t2, &p2);
		int result3 = selectTrack(&t1, &t2);
		Assert::AreEqual(2, result3); //t2 has more volume capacity
	}
	TEST_METHOD(bothTruckFull) {
		struct Truck t1 = { "blue", {0}, 0, 5000.0, 250.0 };
		struct Package p1 = { 5.0, 5000.0 };
		struct Truck t2 = { "green", {0}, 0, 5000.0, 250.0 };
		struct Package p2 = { 250.0, 2000.0 };
		bool result = addPackageToTruck(&t1, &p1);
		bool result2 = addPackageToTruck(&t2, &p2);
		int result3 = selectTrack(&t1, &t2);
		Assert::AreEqual(0, result3); //both truck full
	}
	TEST_METHOD(bothTruckSameCapacity) {
		struct Truck t1 = { "blue", {0}, 0, 5000.0, 250.0 };
		struct Package p1 = { 5.0, 1000.0 };
		struct Truck t2 = { "green", {0}, 0, 5000.0, 250.0 };
		struct Package p2 = { 5.0, 1000.0 };
		bool result = addPackageToTruck(&t1, &p1);
		bool result2 = addPackageToTruck(&t2, &p2);
		int result3 = selectTrack(&t1, &t2);
		Assert::AreEqual(0, result3); //both same capacity
	}
	};
	// Integration test 2
	TEST_CLASS(validateOrderAndSelectTrackIntegration) {
public:
	TEST_METHOD(validOrderSelectTruck1) {

		struct Package package = { 2.0, 1000.0 };
		struct Point destination = { 6, 13 };


		struct Truck t1 = { "blue", {0}, 0, 5000.0, 250.0 };
		struct Truck t2 = { "green", {0}, 0, 2000.0, 200.0 };


		int validationResult = validateOrder(&package, &destination);
		Assert::AreEqual(1, validationResult, L"Order should be valid");

		// should choose 1 with more capacity
		int truckSelection = selectTrack(&t1, &t2);
		Assert::AreEqual(1, truckSelection);
	}

	TEST_METHOD(validOrderSelectTruck2) {

		struct Package package = { 2.0, 1000.0 };
		struct Point destination = { 6, 13 };

		// change t1, t2 truck value
		struct Truck t1 = { "blue", {0}, 0, 2000.0, 200.0 };
		struct Truck t2 = { "green", {0}, 0, 5000.0, 250.0 };


		int validationResult = validateOrder(&package, &destination);
		Assert::AreEqual(1, validationResult);

		// this time should choose t2
		int truckSelection = selectTrack(&t1, &t2);
		Assert::AreEqual(2, truckSelection);
	}

	TEST_METHOD(invalidOrderNoTruckSelection) {
		// Create an invalid package (exceeds maximum weight)
		struct Package package = { 2.0, 6000.0 };
		struct Point destination = { 6, 13 };


		struct Truck t1 = { "blue", {0}, 0, 5000.0, 250.0 };
		struct Truck t2 = { "green", {0}, 0, 5000.0, 250.0 };

		// Validate the order (should fail)
		int validationResult = validateOrder(&package, &destination);
		Assert::AreEqual(0, validationResult, L"Order should be invalid due to weight");

		// Even though we have valid trucks, the order is invalid
		// This test verifies that invalid orders are caught before truck selection
	}

	TEST_METHOD(validOrderEqualTruckCapacity) {

		struct Package package = { 2.0, 1000.0 };
		struct Point destination = { 6, 13 };

		// Create two trucks with equal capacity
		struct Truck t1 = { "blue", {0}, 0, 5000.0, 250.0 };
		struct Truck t2 = { "green", {0}, 0, 5000.0, 250.0 };

		int validationResult = validateOrder(&package, &destination);
		Assert::AreEqual(1, validationResult, L"Order should be valid");

		//both of the trucks should work
		int truckSelection = selectTrack(&t1, &t2);
		Assert::AreEqual(0, truckSelection);
	}
	};
	// Integration test 3
	TEST_CLASS(FindTruckAndDisplayDiversion) {
public:
	FILE* stream;
	FILE* fp;
	void setup(struct Map* map, struct Truck trucks[3], struct Route routes[3]) {
		*map = populateMap();
		routes[0] = getBlueRoute();
		routes[1] = getGreenRoute();
		routes[2] = getYellowRoute();
		initializeTruck(&trucks[0], "Blue");
		initializeTruck(&trucks[1], "Green");
		initializeTruck(&trucks[2], "Yellow");
	}

	TEST_METHOD(IT057OnRouteTest) {
		struct Map map;
		struct Truck trucks[3];
		struct Route routes[3];
		setup(&map, trucks, routes);

		struct ShipmentDetails cargo = { {2.0,100},{11,'L' - 'A'} };
		int truckIndex = findTruck4Shipment(&map, routes, trucks, 3, &cargo);

		Assert::AreEqual(0, truckIndex);

		freopen_s(&stream, "test_output.txt", "w", stdout);
		displayDiversion(&map, &routes[truckIndex], &cargo.destination);
		fclose(stdout);

		fopen_s(&fp, "test_output.txt", "r");
		char buffer[256];
		fgets(buffer, sizeof(buffer), fp);
		fclose(fp);

		freopen_s(&stream, "CON", "w", stdout);

		buffer[strcspn(buffer, "\n")] = 0;

		Assert::AreEqual("no diversion", buffer);
	}

	TEST_METHOD(IT058Ajacent_NoDiversion) {
		struct Map map;
		struct Truck trucks[3];
		struct Route routes[3];
		setup(&map, trucks, routes);

		struct ShipmentDetails cargo = { {2.0,100},{12,'L' - 'A'} };
		int truckIndex = findTruck4Shipment(&map, routes, trucks, 3, &cargo);

		Assert::AreEqual(0, truckIndex);

		freopen_s(&stream, "test_output.txt", "w", stdout);
		displayDiversion(&map, &routes[truckIndex], &cargo.destination);
		fclose(stdout);

		fopen_s(&fp, "test_output.txt", "r");
		char buffer[256];
		fgets(buffer, sizeof(buffer), fp);
		fclose(fp);

		freopen_s(&stream, "CON", "w", stdout);

		buffer[strcspn(buffer, "\n")] = 0;

		Assert::AreEqual("no diversion", buffer);
	}

	TEST_METHOD(IT059Diversion_Required) {
		struct Map map;
		struct Truck trucks[3];
		struct Route routes[3];
		setup(&map, trucks, routes);

		struct ShipmentDetails cargo = { {2.0,100},{7,'Y' - 'A'} };
		int truckIndex = findTruck4Shipment(&map, routes, trucks, 3, &cargo);

		Assert::AreEqual(1, truckIndex);

		freopen_s(&stream, "test_output.txt", "w", stdout);
		displayDiversion(&map, &routes[truckIndex], &cargo.destination);
		fclose(stdout);

		freopen_s(&stream, "CON", "w", stdout);

		fopen_s(&fp, "test_output.txt", "r");
		char buffer[256];
		fgets(buffer, sizeof(buffer), fp);
		fclose(fp);

		buffer[strcspn(buffer, "\n")] = 0;

		// We only check if output starts with "divert:"
		Assert::IsTrue(strncmp(buffer, "divert:", 7) == 0);
	}

	TEST_METHOD(IT060NoTruckAvailable) {
		struct Map map;
		struct Truck trucks[3];
		struct Route routes[3];
		setup(&map, trucks, routes);

		struct ShipmentDetails cargo = { {2.0,5100},{4,'F' - 'A'} };
		int truckIndex = findTruck4Shipment(&map, routes, trucks, 3, &cargo);

		Assert::AreEqual(-1, truckIndex);
	};
	};
	//Integration test 4
	TEST_CLASS(validateUserInput)

	{
		FILE* stream;
		FILE* fp;
	public:
		void mockInput(const char* input) {
			//freopen("mockInput.txt", "w", stdout);
			fopen_s(&fp, "mockInput.txt", "w");
			if (fp)
			{
				fprintf(fp, "%s", input);
				fclose(fp);
			}
			freopen_s(&stream, "mockInput.txt", "r", stdin);
		};
		// Add this at the end of each test method
		void cleanupMock() {
			freopen_s(&stream, "CON", "r", stdin);
		};

		TEST_METHOD(validInput_IT053) {
			mockInput("10 2 12 L\n");
			struct ShipmentDetails order;
			int result = getUserInput(&order);
			cleanupMock();
			Assert::AreEqual(1, result);
		};

		TEST_METHOD(invalidPackage_IT054) {
			mockInput("5500 20 22 F\n");

			struct ShipmentDetails order;
			int result = getUserInput(&order);
			cleanupMock();
			Assert::AreEqual(-1, result);
		};

		TEST_METHOD(invalidDes_IT055) {
			mockInput("2 10 10 N\n");

			struct ShipmentDetails order;
			int result = getUserInput(&order);
			cleanupMock();
			Assert::AreEqual(-1, result);
		};

		TEST_METHOD(edgeCase_IT056) {
			mockInput("5000 5 20 P\n");

			struct ShipmentDetails order;
			int result = getUserInput(&order);
			cleanupMock();
			Assert::AreEqual(1, result);
		};

	};
}