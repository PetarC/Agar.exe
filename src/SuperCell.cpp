#include "SuperCell.h"

void SuperCell::setAbTarget(float pX, float pY)
{
	for (auto iter = cells.begin(); iter != cells.end(); iter++)
		(*iter)->setAbTarget(pX, pY);
}
void SuperCell::setRlTarget(float pX, float pY)
{
	for (auto iter = cells.begin(); iter != cells.end(); iter++)
		(*iter)->setRlTarget(pX, pY);
}
void SuperCell::split(vector<Cell*>* cellList)
{
	for (auto iter = cells.begin(); iter != cells.end(); iter++)
	{
		Cell* temp =(*iter)->split();
		if (temp != nullptr)
			cellList->push_back(temp);
	}
}
void SuperCell::addCell(Cell* newCell)
{
	if (newCell != nullptr)
		cells.push_back(newCell);
}
void SuperCell::removeCell(Cell* newCell)
{
	//This is a stupid function. Suggestions, anyone?
	for (auto iter = cells.begin(); iter != cells.end(); iter++)
	{
		if (*iter == newCell)
			iter = cells.erase(iter); //TODO: Verify this works
	}
}
float SuperCell::getCMassX()
{
	float xPos = 0;
	for (auto iter = cells.begin(); iter != cells.end(); iter++)
		xPos += (*iter)->getX() * (*iter)->getMass();
	xPos /= (float)cells.size();
	return xPos;
}
float SuperCell::getCMassY()
{
	float yPos = 0;
	for (auto iter = cells.begin(); iter != cells.end(); iter++)
		yPos += (*iter)->getY() * (*iter)->getMass();
	yPos /= (float)cells.size();
	return yPos;
}
float SuperCell::getMass()
{
	float mass = 0;
	for (auto iter = cells.begin(); iter != cells.end(); iter++)
		mass += (*iter)->getMass();
	return mass;
}
