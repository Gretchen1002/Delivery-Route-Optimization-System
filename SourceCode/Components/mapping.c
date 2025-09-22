#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mapping.h"
#include "math.h"

struct Map populateMap()
{
	struct Map result = {
		//0	1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4
		//A B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y
		{
		{0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//0
		{0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0},	//1
		{0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0},	//2
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//3
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//4
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//5
		{1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0},	//6
		{1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1},	//7
		{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1},	//8
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//9
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//10
		{1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},	//11
		{1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},	//12
		{1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},	//13
		{1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},	//14
		{1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},	//15
		{0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//16
		{0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//17
		{0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},	//18
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//19
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//20
		{0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0},	//21
		{0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1},	//22
		{0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},	//23
		{0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}		//24
		},
		MAP_ROWS, MAP_COLS
	};
	return result;
}

int getNumRows(const struct Map* map)
{
	return map->numRows;
}

int getNumCols(const struct Map* map)
{
	return map->numCols;
}

void printMap(const struct Map* map, const int base1, const int alphaCols)
{
	//              01234567890123456
	//              1248F
	char sym[] = { " XB?G?.?Y?-?*?+?P" };
	int r, c, rowMax;

	rowMax = map->numRows + base1;

	printf("%4s", " ");
	for (c = 0; c < map->numCols; c++)
	{	
		if (alphaCols) printf("%c", 'A' + c);
		else printf("%d", c % 10);
	}
	printf("\n");
	printf("%4s", " ");
	for (c = 0; c < map->numCols; c++)
	{
		printf("-");
	}
	printf("\n");

	for (r = base1; r < rowMax; r++)
	{
		printf("%3d|", r);
		for (c = 0; c < map->numCols; c++)
		{
			printf("%c", sym[map->squares[r - base1][c]]);
		}
		printf("\n");
	}
}

struct Route getBlueRoute()
{
	struct Route result = {
		{
			{0, 0},
			{1, 0},
			{2, 0},
			{3, 0},
			{4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {4, 7}, {4, 8},{4, 9},
			{5, 9},
			{6, 9},
			{7, 9},
			{8, 9},
			{9, 9},
			{10, 9},{10, 10},
			{11, 10},
			{12, 10},
			{13, 10},
			{14, 10},
			{15, 10},
			{16, 10},
			{17, 10},{17, 11},{17, 12},{17, 13},{17, 14},{17, 15},{17, 16},{17, 17},{17, 18},{17, 19},{17, 20},
				{17, 21},{17, 22},{17, 23},{17, 24},
		},
			42, BLUE
	};
	return result;
}

struct Route getGreenRoute()
{
	struct Route result = {
		{
			{0, 0},
			{1, 0},
			{2, 0},
			{3, 0},
			{4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {4, 7}, {4, 8},{4, 9},{4, 10},{4, 11},
			{3, 11},
			{2, 11},
			{1, 11},
			{0, 11},{0, 12},{0, 13},{0, 14},{0, 15},{0, 16},{0, 17},{0, 18},{0, 19},
			{1, 19},
			{2, 19},
			{3, 19},
			{4, 19},
			{5, 19},
			{6, 19},
			{7, 19},
			{8, 19},
			{9, 19},{9, 20},{9, 21},{9, 22},{9, 23},{9, 24}
			
		},
			42, GREEN
	};
	return result;
}

struct Route getYellowRoute()
{
	struct Route result = {
		{
			{0, 0},
			{1, 0},
			{2, 0},
			{3, 0},
			{4, 0}, {4, 1}, {4, 2}, {4, 3}, 
			{5, 3},
			{6, 3},
			{7, 3},
			{8, 3},
			{9, 3},{9, 2},{9, 1},
			{10, 1},
			{11, 1},
			{12, 1},
			{13, 1},
			{14, 1},
			{15, 1},
			{16, 1},
			{17, 1},
			{18, 1},
			{19, 1},{19, 2},{19, 3},{19, 4},{19, 5},{19, 6},{19, 7},{19, 8},{19, 9},{19, 10},{19, 11},{19, 12},
				{19, 13},{19, 14},{19, 15},{19, 16},{19, 17},{19, 18},{19, 19},{19, 20},{19, 21},{19, 22},{19, 23},{19, 24}
		},
			48, YELLOW
	};
	return result;
}

struct Map addRoute(const struct Map* map, const struct Route* route)
{
	int r, c;
	struct Map result = { {0}, 0 };

	for (r = 0; r < map->numRows; r++)
	{
		for (c = 0; c < map->numCols; c++)
		{
			result.squares[r][c] = map->squares[r][c];
		}
	}
	result.numRows = map->numRows;
	result.numCols = map->numCols;

	for (r = 0; r < route->numPoints; r++)
	{
		result.squares[route->points[r].row][route->points[r].col] += route->routeSymbol;
	}

	return result;
}

void addPtToRoute(struct Route* route, struct Point pt)
{
	route->points[route->numPoints++] = pt;
}

void addPointToRoute(struct Route* route, const int row, const int col)
{
	struct Point pt = { row, col };
	addPtToRoute(route, pt);
}

void addPointToRouteIfNot(struct Route* route, const int row, const int col, const struct Point notThis)
{
	struct Point pt = { row, col };
	if(notThis.row != row || notThis.col != col) addPtToRoute(route, pt);
}

double distance(const struct Point* p1, const struct Point* p2)
{
	int deltaRow = p2->row - p1->row;
	int deltaCol = p2->col - p1->col;

	return sqrt((double)(deltaRow * deltaRow + deltaCol * deltaCol));
}

struct Route shortestPath(const struct Map* map, const struct Point start, const struct Point dest)
{
	struct Route result = { {0,0}, 0, DIVERSION };
	struct Point targetDest = dest;
	
	if (eqPt(start, targetDest)) {
		addPtToRoute(&result, start);
		return result;
	}

	// Check if destination is a building
	if (map->squares[targetDest.row][targetDest.col] == 1) {
		int dr[] = {0, -1, 0, 1, 0};  // Prioritize cardinal directions
		int dc[] = {0, 0, 1, 0, -1};
		
		int foundValidSpot = 0;
		
		for (int i = 0; i < 5; i++) {
			int newRow = targetDest.row + dr[i];
			int newCol = targetDest.col + dc[i];
			
			if (newRow >= 0 && newRow < MAP_ROWS && 
				newCol >= 0 && newCol < MAP_COLS && 
				map->squares[newRow][newCol] != 1) {
				targetDest.row = newRow;
				targetDest.col = newCol;
				foundValidSpot = 1;
				break;
			}
		}
		
		if (!foundValidSpot) {
			return result;
		}
	}

	// Initialize distance array with infinity
	double distances[MAP_ROWS][MAP_COLS];
	for (int i = 0; i < MAP_ROWS; i++) {
		for (int j = 0; j < MAP_COLS; j++) {
			distances[i][j] = 999999.99;
		}
	}
	distances[start.row][start.col] = 0;

	struct Point previous[MAP_ROWS][MAP_COLS];
	struct Point queue[MAP_ROWS * MAP_COLS];
	int front = 0, rear = 0;
	
	queue[rear++] = start;
	
	// Movement directions: straight first, then diagonal
	int dr[] = {-1, 1, 0, 0, -1, -1, 1, 1};
	int dc[] = {0, 0, -1, 1, -1, 1, -1, 1};
	double costs[] = {1.0, 1.0, 1.0, 1.0, 1.414, 1.414, 1.414, 1.414};  // Diagonal moves cost more
	
	int found = 0;
	
	while (front < rear && !found) {
		// Find point with minimum distance
		double minDist = 999999.99;
		int minIdx = front;
		for (int i = front; i < rear; i++) {
			if (distances[queue[i].row][queue[i].col] < minDist) {
				minDist = distances[queue[i].row][queue[i].col];
				minIdx = i;
			}
		}
		
		// Move the minimum distance point to front
		struct Point temp = queue[front];
		queue[front] = queue[minIdx];
		queue[minIdx] = temp;
		
		struct Point current = queue[front++];
		
		if (eqPt(current, targetDest)) {
			found = 1;
			break;
		}
		
		for (int i = 0; i < 8; i++) {
			struct Point next = {current.row + dr[i], current.col + dc[i]};
			
			if (next.row < 0 || next.row >= MAP_ROWS || 
				next.col < 0 || next.col >= MAP_COLS)
				continue;
				
			if (map->squares[next.row][next.col] == 1)
				continue;
			
			// For diagonal moves, check both adjacent squares
			if (i >= 4) {  // diagonal moves
				if (map->squares[current.row][next.col] == 1 || 
					map->squares[next.row][current.col] == 1)
					continue;
			}
			
			double newDist = distances[current.row][current.col] + costs[i];
			
			if (newDist < distances[next.row][next.col]) {
				distances[next.row][next.col] = newDist;
				previous[next.row][next.col] = current;
				
				// Add to queue if not already there
				int inQueue = 0;
				for (int j = front; j < rear; j++) {
					if (eqPt(queue[j], next)) {
						inQueue = 1;
						break;
					}
				}
				if (!inQueue) {
					queue[rear++] = next;
				}
			}
		}
	}
	
	if (found) {
		struct Point current = targetDest;
		struct Route reversePath = { {0,0}, 0, DIVERSION };
		
		while (!eqPt(current, start)) {
			addPtToRoute(&reversePath, current);
			current = previous[current.row][current.col];
		}
		addPtToRoute(&reversePath, start);
		
		for (int i = reversePath.numPoints - 1; i >= 0; i--) {
			addPtToRoute(&result, reversePath.points[i]);
		}
	}
	
	return result;
}

struct Route getPossibleMoves(const struct Map* map, const struct Point p1, const struct Point backpath)
{
	struct Route result = { {0,0}, 0, DIVERSION };

	if (p1.row > 0 )
	{
		if(map->squares[p1.row - 1][p1.col] != 1) addPointToRouteIfNot(&result, p1.row - 1, p1.col, backpath);	// square above
		if (p1.col > 0 && map->squares[p1.row - 1][p1.col-1] != 1) addPointToRouteIfNot(&result, p1.row - 1, p1.col-1, backpath);	// top left
		if (p1.col < (map->numCols-1) && map->squares[p1.row - 1][p1.col + 1] != 1) addPointToRouteIfNot(&result, p1.row - 1, p1.col + 1, backpath);	// top right
	}
	if(p1.col > 0 && map->squares[p1.row][p1.col - 1] != 1)addPointToRouteIfNot(&result, p1.row, p1.col - 1, backpath);	// left
	if (p1.col < (map->numCols - 1) && map->squares[p1.row][p1.col + 1] != 1)addPointToRouteIfNot(&result, p1.row, p1.col + 1, backpath);	// right
	if (p1.row < (map->numRows - 1))
	{
		if (map->squares[p1.row + 1][p1.col] != 1) addPointToRouteIfNot(&result, p1.row + 1, p1.col, backpath);	// square below
		if (p1.col > 0 && map->squares[p1.row + 1][p1.col - 1] != 1) addPointToRouteIfNot(&result, p1.row + 1, p1.col - 1, backpath);	// bot left
		if (p1.col < (map->numCols - 1) && map->squares[p1.row + 1][p1.col + 1] != 1) addPointToRouteIfNot(&result, p1.row + 1, p1.col + 1, backpath);	// top right
	}

	return result;
}

int eqPt(const struct Point p1, const struct Point p2)
{
	return p1.row == p2.row && p1.col == p2.col;
}

int getClosestPoint(const struct Route* route, const struct Point pt)
{
	int i, closestIdx = -1;
	double closestDist = 999999.99, dist;

	for (i = 0; i < route->numPoints; i++)
	{
		dist = distance(&pt, &route->points[i]);
		if (dist < closestDist)
		{
			closestDist = dist;
			closestIdx = i;
		}
	}
	return closestIdx;
}
