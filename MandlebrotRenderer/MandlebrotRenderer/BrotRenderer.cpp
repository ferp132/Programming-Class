#include "BrotRenderer.h"

BrotRenderer::BrotRenderer()
{
}

BrotRenderer::BrotRenderer(int* brotarray, int InitLine, SDL_Renderer * InitRenderer,
							long double InitMin, long double InitMax, 
							int InitMaxIts, int InitWidth, int InitHeight)
{
	BrotArray = brotarray;
	Line = InitLine;
	RendererID = InitRenderer;
	Min = InitMin;
	Max = InitMax;
	MaxIts = InitMaxIts;
	WIDTH = InitWidth;
	HEIGHT = InitHeight;
	ZoomFactor = 1;

	tempArray = new int[800];

}

BrotRenderer::~BrotRenderer()
{
}

void BrotRenderer::Render(int x, int NumIts)
{
}

int BrotRenderer::CalcColourR(int Brightness)
{
	return (int)(Map(Brightness * Brightness, 0, 255 * 255, 0, 255));
}

int BrotRenderer::CalcColourG(int Brightness)
{
	return (int)(Map(Brightness - Brightness / 2, 0, 255 - 255 / 2, 0, 255));
}

int BrotRenderer::CalcColourB(int Brightness)
{
	return (int)(Map(Brightness + Brightness / 2, 0, 255 + 255 / 2, 0, 255));
}

void BrotRenderer::CalculateBrot()
{
	for (int x = 0; x < WIDTH; x++)
	{
			int NumIts = 0;

			long double a = Map(x, 0, WIDTH, Min, Max);
			long double b = Map(Line, 0, HEIGHT, Min, Max);

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

			int Brightness = (int)(Map(NumIts, 0, MaxIts, 0, 255));
			if (NumIts == MaxIts || Brightness < 30)
				Brightness = 0;

			tempArray[x] = Brightness;
	}
}

long double BrotRenderer::Map(long double Value, long double MinIn, long double MaxIn, long double MinOut, long double MaxOut)
{
	return (Value - MinIn) * (MaxOut - MinOut) / (MaxIn - MinIn) + MinOut;
}