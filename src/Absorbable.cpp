#include "Absorbable.h"

Absorbable::Absorbable(int newMass)
{
	mass = newMass;
	posX = posY = 0;

	//Select a new color, using the HSL color wheel for bright colors.
	ColorHSL temp;
	temp.setH((rand() % 360) + 1);
	temp.setS(1);
	temp.setL(.5f);

	color = temp.getRGB();
	temp.setL(0.25f);
	accentColor = temp.getRGB();
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
	//Draw a circle... actually a square for now. Sorry!
	double radius = mass * scale; //TODO: Ensure that this formula works as intended...
	SDL_Rect rect;
	rect.x = posX - (vPosX * scale) - (radius * scale / 2.f);
	rect.y = posY - (vPosY * scale) - (radius * scale / 2.f);
	rect.h = radius,
	rect.w = radius;

	SDL_SetRenderDrawColor(renderer, color.getR(), color.getG(), color.getB(), 255);
	SDL_RenderFillRect(renderer, &rect);

	//Border
	rect.x--;
	rect.y--;
	rect.h += 2;
	rect.w += 2;
	SDL_SetRenderDrawColor(renderer, accentColor.getR(), accentColor.getG(), accentColor.getB(), 255);
	for (int i = radius; i >= radius - 5; --i)
	{
		rect.x++;
		rect.y++;
		rect.h -= 2;
		rect.w -= 2;
		SDL_RenderDrawRect(renderer, &rect);
	}
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
SDL_Rect Absorbable::getRect()
{
	double radius = mass; //TODO: Ensure that this formula works as intended...
	SDL_Rect rect;
	rect.x = posX;
	rect.y = posY;
	rect.h = radius,
	rect.w = radius;
	return rect;
}
