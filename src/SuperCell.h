#pragma once

#include "Cell.h"
#include <vector>
using std::vector;

//Grouping of cells that should all be under control of a single cell.
class SuperCell
{
public:
	void setAbTarget(float pX, float pY); //Relative to grid
	void setRlTarget(float px, float pY); //Relative to center of mass
	void moveToTarget(); //Just calls the moveToTarget() function of all its controlled cells.
	void split(vector<Cell*>* cellList); //The cells vector is passed so this supercell can add on cells to the list.
	void addCell(Cell* newCell);
	void removeCell(Cell* newCell); //TODO: Unstupidify

	float getCMassX(); //Get the X center of mass
	float getCMassY(); //Get the Y center of mass
	float getMass(); //Get the total mass.
private:
	float massX;
	float massY;
	vector<Cell*> cells; //Vector of pointers to cells this scell has control over; pointers because cells must be stored separately for collision reasons
};
