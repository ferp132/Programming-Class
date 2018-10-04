#include <Windows.h>
#include <SDL.h>

int WIDTH = 800;
int HEIGHT = 800;

int MaxIts = 500;			//Max Iterations :: How many times the mandlebrot function will be applied. Higher values will result in more defined geometry (good for zooming)

long double min = -2.0;		
long double max =  2.0;

long double ZoomFactor = 1;

long double map(long double Value, long double in_min, long double in_max, long double out_min, long double out_max)
{
	return (Value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(1920, 1080, 0, &window, &renderer);
	SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);

//	int count = 0;

	bool Exit = false;
	while (!Exit)
	{

		WIDTH += 10;
		HEIGHT += 10;

//		max -= 0.1 * ZoomFactor;
//		min += 0.15 * ZoomFactor;
//		ZoomFactor *= 0.9;
//		MaxIts += 10;

//		if (count > 30)
//			MaxIts *= 1.02;

		SDL_RenderPresent(renderer);

		for (int x = 0; x < WIDTH; x++)		 // x = a
		{
			if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
				return 0;
			if (GetKeyState('Q') & 0x8000)
				return 0;
			if (GetKeyState('A') & 0x8000)
			{
			}
			if (GetKeyState('D') & 0x8000)
			{
			}

			for (int y = 0; y < HEIGHT; y++) // y = b	
			{
				
				long double a = map(x, 0, WIDTH, min, max);
				long double b = map(y, 0, HEIGHT, min, max);

				long double oa = a;
				long double ob = b;

				int NumIts = 0;

				//-----Do math
				for (int i = 0; i < MaxIts; i++)
				{
					long double fa = a * a - b * b;				// x^2 - y^2
					long double fb = 2 * a * b;					// 2 * x * y * c (ignore c)
				
					a = oa + fa;
					b = ob + fb;

					if (a + b > 2)
						break;

					NumIts++;
				}

				//-----Set Colours
				int Brightness = map(NumIts, 0, MaxIts, 0, 255);
				//-----Do Draw
				if (NumIts == MaxIts || Brightness < 30)
					Brightness = 0;

				

				int R = Brightness + Brightness;
				int G = Brightness * 2;
				int B = Brightness / 2;

				SDL_SetRenderDrawColor(renderer, R, G, B, 255);
				SDL_RenderDrawPoint(renderer, x, y);
			}
		}
		//count++;
	}


	return 0;
}