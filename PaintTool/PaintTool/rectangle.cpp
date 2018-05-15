#include "rectangle.h"

CRectangle::CRectangle(EBRUSHSTYLE _iBrushStyle, int _iHatchStyle, COLORREF _FillColor, int _iPenStyle, int _iPenWidth, COLORREF _PenColor, int _X, int _Y)
{
	m_iBrushStyle = _iBrushStyle;
	m_iHatchStyle = _iHatchStyle;
	m_iFillColor = _FillColor;
	m_iPenStyle = _iPenStyle;
	m_iPenWidth = _iPenWidth;
	m_iPenColor = _PenColor;
	m_iStartX = _X;
	m_iStartY = _Y;
}

CRectangle::CRectangle()
{
}

CRectangle::~CRectangle()
{
}

void CRectangle::Draw(HDC _hdc)
{
	// Create Pen & Brush
	HPEN hPen;
	HBRUSH hBrush;

	//Initialise & Select Pen
	hPen = CreatePen(m_iPenStyle, m_iPenWidth, m_iPenColor);
	SelectObject(_hdc, hPen);

	//Initialise & Select Brush
	switch (m_iBrushStyle)
	{
	case NOSTYLE:
	{
		SelectObject(_hdc, GetStockObject(NULL_BRUSH));
		break;
	}
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

	//Draw Rectangle
	Rectangle(_hdc, m_iStartX, m_iStartY, m_iEndX, m_iEndY);

	//Delete pens after use
	DeleteObject(hPen);
	if (GetCurrentObject(_hdc, OBJ_BRUSH) == GetStockObject(NULL_BRUSH)) return; // If the Brush is Hollow, Just return.
	else DeleteObject(hBrush);													 // Otherwise Delete The Brush We Created
}