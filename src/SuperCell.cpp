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
void SuperCell::moveToTarget()
{
	for (auto iter = cells.begin(); iter != cells.end(); iter++)
		(*iter)->moveToTarget();
}
void SuperCell::split(vector<Cell*>* cellList)
{
	vector<Cell*> cellBuffer; //needed so we don't try to split newly split cells
	for (auto iter = cells.begin(); iter != cells.end(); iter++)
	{
		Cell* temp =(*iter)->split();
		if (temp != nullptr)
		{
			cellList->push_back(temp);
			cellBuffer.push_back(temp);
		}
	}
	for (auto iter = cellBuffer.begin(); iter != cellBuffer.end(); iter++)
		addCell(*iter);
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
	xPos /= getMass() * (float)cells.size();
	return xPos;
}
float SuperCell::getCMassY()
{
	float yPos = 0;
	for (auto iter = cells.begin(); iter != cells.end(); iter++)
		yPos += (*iter)->getY() * (*iter)->getMass();
	yPos /= getMass() * (float)cells.size();
	return yPos;
}
float SuperCell::getMass()
{
	float mass = 0;
	for (auto iter = cells.begin(); iter != cells.end(); iter++)
		mass += (*iter)->getMass();
	return mass;
}
