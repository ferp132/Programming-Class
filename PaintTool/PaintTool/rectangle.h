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

#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

//	Library Includes
#include <windows.h>
#include <windowsx.h>
#include "shape.h"




class CRectangle : public IShape
{
public:
	CRectangle(EBRUSHSTYLE _iBrushStyle, int _iHatchStyle, COLORREF _FillColor, int _iPenStyle, int _iPenwidth, COLORREF _PenColor, int _X, int _Y);
	CRectangle();
	virtual ~CRectangle();

	virtual void Draw(HDC _hdc);

private:
	EBRUSHSTYLE m_iBrushStyle;
	int m_iHatchStyle;
	COLORREF m_iFillColor;
	int m_iPenStyle;
	int m_iPenWidth;
	int m_iPenColor;
	COLORREF m_PenColor;
};

#endif