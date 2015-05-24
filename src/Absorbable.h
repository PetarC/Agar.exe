#pragma once

#include "../lib/Hydra Engine/Hydra.h"
using namespace Hydra;

//A generic class for any object that can be absorbed.
class Absorbable
{
public:
	Absorbable(int newMass = 1);
	void absorb(Absorbable* object);
	void draw(SDL_Renderer* renderer, float vPosX, float vPosY, float scale);

	void setMass(float newMass);
	void setX(float newX);
	void setY(float newY);
	float getX();
	float getY();
	float getMass();
protected:
	float posX, posY;
	float mass;
	ColorRGB color;
};
