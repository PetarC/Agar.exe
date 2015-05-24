#include "Cell.h"

Cell::Cell(int newMass) : Absorbable(newMass)
{
	tDir.setX(0); tDir.setY(0);
	vel.setX(0); vel.setY(0);
}
void Cell::setAbTarget(float pX, float pY)
{
	tDir.setX(pX - posX);
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
	float maxSpeed = (cellForce / mass * 2.75) * cellSpeed;

	if (tDir.getMag() > accel)
		tDir.setMag(accel);
	vel = vel + tDir;
	if (vel.getMag() > maxSpeed)
		vel.setMag(maxSpeed);

	posX += vel.getX();
	posY += vel.getY();
}