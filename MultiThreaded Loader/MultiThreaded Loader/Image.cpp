#include "Image.h"

Image::Image(HINSTANCE InitInstanceHandle)
{
	InstanceHandle = InitInstanceHandle;

	xPos = 0;
	yPos = 0;
}

Image::~Image()
{
	DeleteObject(SpriteHandle);
	DeleteObject(MaskHandle);
}

bool Image::Initialise(int SpriteID, int MaskID)
{
	SpriteHandle = LoadBitmap(InstanceHandle, MAKEINTRESOURCE(SpriteID));
	MaskHandle = LoadBitmap(InstanceHandle, MAKEINTRESOURCE(MaskID));

	GetObject(SpriteHandle, sizeof(BITMAP), &SpriteBitmap);
	GetObject(MaskHandle, sizeof(BITMAP), &MaskBitmap);

	return false;
}

void Image::Draw()
{
}

int Image::GetWidth() const
{
	return 0;
}

int Image::GetHeight() const
{
	return 0;
}

int Image::GetX() const
{
	return 0;
}

int Image::GetY() const
{
	return 0;
}

void Image::SetX(int _i)
{
}

void Image::SetY(int _i)
{
}
