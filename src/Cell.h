#pragma once

#include "Absorbable.h"

#define cellForce 20.f //The force a cell can apply (physics)
#define cellSpeed 15.f //Max speed of a unit cell
#define minSplitSize 40 //Minimum size needed to split.
#define absorbPercent 1.2f //The fraction the other cell's mass must be in order to be absorbed

class Cell : public Absorbable
{
public:
	Cell(int newMass);
	void setAbTarget(float pX, float pY); 	//Absolute target
	void setRlTarget(float pX, float pY);	//Target relative to cell
	void move();							//Moves the cell.
	void moveToTarget();					//Changes velocity to go toward the target. You still need to call move() to effect a position change.
	Cell* split(); 							//Splits this cell into two equal parts. Returns a pointer to the new cell object, created on the heap.
	Vector2D getVel();						//Gets the velocity of this cell.
	void setVel(Vector2D newVel);			//Sets the velocity of this cell.
private:
	Vector2D tDir; //Direction to target
	Vector2D vel;
};
