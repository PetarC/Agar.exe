#pragma once

#include "Absorbable.h"

#define cellForce 20.f //The force a cell can apply (physics)
#define cellSpeed 3.5f //Max speed of a unit cell
#define minSplitSize 40 //Minimum size needed to split.

class Cell : public Absorbable
{
public:
	Cell(int newMass);
	void setAbTarget(float pX, float pY); 	//Absolute target
	void setRlTarget(float pX, float pY);	//Target relative to cell
	void move();							//Moves the cell.
	void moveToTarget();					//Changes velocity to go toward the target. You still need to call move() to effect a position change.
	Cell* split(); 							//Splits this cell into two equal parts. Returns a pointer to the new cell object, created on the heap.
private:
	Vector2D tDir; //Direction to target
	Vector2D vel;
};
