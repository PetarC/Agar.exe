#include "Cell.h"

Cell::Cell(int newMass) : Absorbable(newMass)
{
	tDir.setX(0); tDir.setY(0);
	vel.setX(0); vel.setY(0);
}
void Cell::setAbTarget(float pX, float pY)
{
	tDir.setX(pX - posX); //TODO: Ensure relative position calculation works
	tDir.setY(pY - posY);
}
void Cell::setRlTarget(float pX, float pY)
{
	tDir.setX(pX);
	tDir.setY(pY);
}
void Cell::move()
{
	float accel = cellForce / mass;
	float maxSpeed = cellSpeed / mass; //This might need to change

	if (tDir.getMag() > accel)
		tDir.setMag(accel);
	vel = vel + tDir;
	if (vel.getMag() > maxSpeed)
		vel.setMag(maxSpeed);
	posX += vel.getX();
	posY += vel.getY();
}
