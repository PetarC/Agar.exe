#pragma once

#include "Absorbable.h"

#define cellForce 20.f //The force a cell can apply (physics)
#define cellSpeed 4.5f //Max speed of a unit cell

class Cell : public Absorbable
{
public:
	Cell(int newMass);
	void setAbTarget(float pX, float pY); 	//Absolute target
	void setRlTarget(float pX, float pY);	//Target relative to cell
	void move();							//Moves the cell using its target information
private:
	Vector2D tDir; //Direction to target
	Vector2D vel;
};