#pragma once

#if !defined(__IMAGE_H__)
#define __IMAGE_H__

#include "windows.h"

class Image
{
	// Member Functions
public:
	Image(HINSTANCE InitInstanceHandle);
	~Image();

	bool Initialise(int SpriteID, int MaskID);

	void Draw();

	int GetWidth() const;
	int GetHeight() const;

	int GetX() const;
	int GetY() const;
	void SetX(int _i);
	void SetY(int _i);


private:

	int xPos;
	int yPos;

	HBITMAP SpriteHandle;
	HBITMAP MaskHandle;

	BITMAP SpriteBitmap;
	BITMAP MaskBitmap;

	HINSTANCE InstanceHandle;

	//static HDC SharedSpriteDC;
};

#endif    // __SPRITE_H__
