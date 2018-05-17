/***********************
  Bachelor of Software Engineering
  Media Design School
  Auckland
  New Zealand

  (c) 2018 Media Design School

  File Name   :   [Filename]
  Description :   [One line description of what is the file is for]
  Author      :   [Your name]
  Mail        :   [your.name]@mediadesign.school.nz
********************/


#ifndef __ELLIPSE_H__
#define __ELLIPSE_H__

//	Library Includes
#include <windows.h>
#include <windowsx.h>

#include "shape.h"


class CEllipse : public IShape
{
public:
	CEllipse(EBRUSHSTYLE _iBrushStyle, int _iHatchStyle, COLORREF _FillColor, int _iPenStyle, int _iPenWidth, COLORREF _PenColor, int _X, int _Y, COLORREF _bgColor, int _bgMode);
	CEllipse();
	virtual ~CEllipse();

	virtual void Draw(HDC _hdc);
private:
	COLORREF m_bgColor;
	int m_bgMode;
	EBRUSHSTYLE m_iBrushStyle;
	int m_iHatchStyle;
	COLORREF m_iFillColor;
	int m_iPenStyle;
	int m_iPenWidth;
	int m_iPenColor;
	COLORREF m_Color;
};

#endif