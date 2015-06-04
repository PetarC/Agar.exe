#include "../lib/Hydra Engine/Hydra.h"
#include "Absorbable.h"
#include "Cell.h"
#include "SuperCell.h"
using namespace Hydra;

#define GRID_X 20
#define GRID_Y 20
#define WINDOW_X 800
#define WINDOW_Y 600

void drawGrid(int xPos, int yPos, double scale = 1.0);
inline bool colliding(SDL_Rect rect1, SDL_Rect rect2);
inline double getScale(SDL_Rect dims);

int main(int argc, char* argv[])
{
	srand(SDL_GetTicks());
	HydraEngine* engine = HydraEngine::getInstance();
	engine->init();
	engine->setWSize(WINDOW_X, WINDOW_Y);
	engine->setWTitle("Agar.exe, the free port of Agar.io");
	SDL_Renderer* renderer = engine->getRenderer();


	vector<Cell*> cells;
	SuperCell playerCells;
	Cell cell(800);
	cells.push_back(&cell);
	playerCells.addCell(&cell);
	double scale = getScale(playerCells.getDims());

	float vX = 0, vY = 0; //Viewer X and Y

	bool quit = false;
	while (!quit)
	{
		Timer fps;
		fps.start();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				quit = true;
			if (event.key.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_SPACE)
				playerCells.split(&cells);
		}

		int mX, mY;
		SDL_GetMouseState(&mX, &mY);

		vX = playerCells.getCMassX(); //Viewer coordinates dependent on the supercell's center of mass
		vY = playerCells.getCMassY();
		playerCells.setAbTarget(mX + vX - (engine->getWXSize() / 2.f), mY + vY - (engine->getWYSize() / 2.f));
		playerCells.moveToTarget();

		//Determine scaling
		double tempScale = getScale(playerCells.getDims());
		if (fabs(scale - tempScale) >  tempScale * 0.02)
			scale < tempScale ? scale += (0.005 * tempScale) : scale -= (0.005 * tempScale);
		else
			scale = tempScale;
		if (scale > 1.f)
			scale = 1.f; //No zooming in!
		cout << "Scale: " << scale << endl;
		SDL_Rect dims = playerCells.getDims();
		cout << "SCell dims: " << dims.x << ", " << dims.y << " , " << dims.w << ", " << dims.h << endl;

		//Graphics
		SDL_RenderClear(renderer);
		drawGrid(-vX, -vY, scale);

		for (auto iter = cells.begin(); iter != cells.end(); iter++)
		{
			if (*iter == nullptr)
				continue;
			(*iter)->move();
			(*iter)->draw(renderer, (vX * scale) - (engine->getWXSize() / 2.f), (vY * scale) - (engine->getWYSize() / 2.f), scale);
		}

		SDL_RenderPresent(renderer);
		while (fps.getTime() < 16);
	}
	engine->shutdown();
}

void drawGrid(int xPos, int yPos, double scale)
{
	//Draw in the background, a dark grey color
	SDL_Rect rect;
	HydraEngine* engine = HydraEngine::getInstance();
	rect.x = 0; rect.y = 0;
	rect.w = engine->getWXSize(); rect.h = engine->getWYSize();
	SDL_SetRenderDrawColor(engine->getRenderer(), 39, 39, 39, 255);
	SDL_RenderFillRect(engine->getRenderer(), &rect);

	//Draw in the grid
	SDL_SetRenderDrawColor(engine->getRenderer(), 125, 125, 125, 255);
	for (int iX = -xPos / GRID_X; iX <= (1.f / scale) * (engine->getWXSize() / GRID_X) + fabs(scale * (float)xPos); iX++)
		SDL_RenderDrawLine(engine->getRenderer(), (iX * GRID_X * scale) + (xPos * scale), 0, (iX * GRID_X * scale) + (xPos * scale), engine->getWYSize());

	for (int iY = -yPos / GRID_Y; iY <= (1.f / scale) * (engine->getWYSize() / GRID_Y) + fabs(scale * (float)yPos); iY++)
		SDL_RenderDrawLine(engine->getRenderer(), 0, (iY * GRID_Y * scale) + (yPos * scale), engine->getWXSize(), (iY * GRID_Y * scale) + (yPos * scale));
}
bool colliding(SDL_Rect rect1, SDL_Rect rect2)
{
	SDL_Rect result;
	if (SDL_IntersectRect(&rect1, &rect2, &result) == SDL_TRUE)
		return true;
	else
		return false;
}
double getScale(SDL_Rect dims)
{
	if (dims.w > dims.h)
		return (double)WINDOW_X / (double)dims.w;
	else
		return (double)WINDOW_Y / (double)dims.h;
}
