#include "Absorbable.h"

Absorbable::Absorbable(int newMass)
{
	mass = newMass;
	posX = posY = 0;

	//Select a new color, using the HSL color wheel for bright colors.
	ColorHSL temp;
	temp.setH((rand() % 360) + 1);
	temp.setS(1);
	temp.setL(.5);

	color = temp.getRGB();
}
void Absorbable::absorb(Absorbable* object)
{
	mass += object->mass;

	//Do a neat averaging of colors thing, to make it look like something was really absorbed
	ColorHSL temp1 =color.getHSL(), temp2 = object->color.getHSL();
	temp1.setH((temp1.getH() + temp2.getH()) / 2);
	color = temp1.getRGB();
}
void Absorbable::draw(SDL_Renderer* renderer, float vPosX, float vPosY, float scale)
{
	SDL_SetRenderDrawColor(renderer, color.getR(), color.getG(), color.getB(), 255);

	//Draw a circle... actually a square for now. Sorry!
	double radius = log2(mass) * scale * 10.f; //TODO: Ensure that this formula works as intended...
	SDL_Rect rect;
	rect.x = posX - (vPosX * scale), rect.y = posY - (vPosY * scale);
	rect.h = radius, rect.w = radius;
	SDL_RenderFillRect(renderer, &rect);
}
void Absorbable::setMass(float newMass)
{
	mass = newMass;
}
void Absorbable::setX(float newX)
{
	posX = newX;
}
void Absorbable::setY(float newY)
{
	posY = newY;
}
float Absorbable::getX()
{
	return posX;
}
float Absorbable::getY()
{
	return posY;
}
float Absorbable::getMass()
{
	return mass;
}

