#include "BrotRenderer.h"

BrotRenderer::BrotRenderer(SDL_Renderer * InitRenderer, long double InitMin, long double InitMax, int InitMaxIts, int InitWidth, int InitHeight)
{

}

BrotRenderer::~BrotRenderer()
{
}

void BrotRenderer::CalcColour(int R, int G, int B)
{
}

void BrotRenderer::Render()
{
}

int BrotRenderer::CalculateBrot()
{
	int NumIts = 0;

	for (int x = 0; x < WIDTH; x++)		 // x = a
	{
		for (int y = 0; y < HEIGHT; y++) // y = b	
		{

			long double a = Map(x, 0, WIDTH, Min, Max);
			long double b = Map(y, 0, HEIGHT, Min, Max);

			long double oa = a;
			long double ob = b;

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
		}
	}
		return NumIts;
}

long double BrotRenderer::Map(long double Value, long double MinIn, long double MaxIn, long double MinOut, long double MaxOut)
{
	return (Value - MinIn) * (MaxOut - MinOut) / (MaxIn - MinIn) + MinOut;
}
