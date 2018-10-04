#pragma once
#include <SDL.h>

class BrotRenderer
{
private:
	SDL_Renderer* RendererID;

	long double Min;
	long double Max;

	long double ZoomFactor;

	int MaxIts;																											//Max Iterations :: How many times the mandlebrot function will be applied. Higher values will result in more defined geometry (good for zooming)
	
	int WIDTH;
	int HEIGHT;

public:
	BrotRenderer(SDL_Renderer* InitRenderer, long double InitMin = -2.0, long double InitMax = 2.0, int InitMaxIts = 200, int InitWidth = 1000, int InitHeight = 1000);
	~BrotRenderer();

	void		DoJob();
	void		CalcColour(int R, int G, int B);
	void		Render();
	int CalculateBrot();
	long double Map(long double Value,
		long double MinIn, long double MaxIn,
		long double MinOut, long double MaxOut);
	

};