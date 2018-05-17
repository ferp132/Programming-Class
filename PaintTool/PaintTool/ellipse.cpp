#include "ellipse.h"

CEllipse::CEllipse(EBRUSHSTYLE _iBrushStyle, int _iHatchStyle, COLORREF _FillColor, int _iPenStyle, int _iPenWidth, COLORREF _PenColor, int _X, int _Y, COLORREF _bgColor, int _bgMode)
{
	m_iBrushStyle = _iBrushStyle;
	m_iHatchStyle = _iHatchStyle;
	m_iFillColor = _FillColor;
	m_iPenStyle = _iPenStyle;
	m_iPenWidth = _iPenWidth;
	m_iPenColor = _PenColor;
	m_iStartX = _X;
	m_iStartY = _Y;
	m_bgMode = _bgMode;
	m_bgColor = _bgColor;
}

CEllipse::CEllipse()
{
}

CEllipse::~CEllipse()
{
}

void CEllipse::Draw(HDC _hdc)
{
	// Create Pen & Brush
	HPEN hPen;
	HBRUSH hBrush;

	SetBkColor(_hdc, m_bgColor);
	SetBkMode(_hdc, m_bgMode);

	//Initialise & Select Pen
	hPen = CreatePen(m_iPenStyle, m_iPenWidth, m_iPenColor);
	SelectObject(_hdc, hPen);

	//Initialise & Select Brush
	switch (m_iBrushStyle)
	{
	case SOLID:
	{
		hBrush = CreateSolidBrush(m_iFillColor);
		SelectObject(_hdc, hBrush);
		break;
	}
	case HATCH:
	{
		hBrush = CreateHatchBrush(m_iHatchStyle, m_iFillColor);
		SelectObject(_hdc, hBrush);
		break;
	}
	default:break;
	}

	//Draw Ellipse
	Ellipse(_hdc, m_iStartX, m_iStartY, m_iEndX, m_iEndY);

	//Delete pens after use
	DeleteObject(hPen);
	DeleteObject(hBrush);													 // Otherwise Delete The Brush We Created
}

