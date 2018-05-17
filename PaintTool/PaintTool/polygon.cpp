#include "polygon.h"

CPolygon::CPolygon(EBRUSHSTYLE _iBrushStyle, int _iHatchStyle, COLORREF _FillColor, int _iPenStyle, int _iPenWidth, COLORREF _PenColor, int _X, int _Y, COLORREF _bgColor, int _bgMode)
{
	m_iBrushStyle = _iBrushStyle;
	m_iHatchStyle = _iHatchStyle;
	m_iFillColor = _FillColor;
	m_iPenStyle = _iPenStyle;
	m_iPenWidth = _iPenWidth;
	m_iPenColor = _PenColor;
	m_nPoints = 0;
	TempPoint.x = _X;
	TempPoint.y = _Y;
	m_iEndX = _X;
	m_iEndY = _Y;
	AddPoint(TempPoint);
	m_bgMode = _bgMode;
	m_bgColor = _bgColor;
}

CPolygon::CPolygon()
{
}

CPolygon::~CPolygon()
{
}

void CPolygon::AddPoint(POINT p)
{
		m_pPointList[m_nPoints] = p;
		m_nPoints++;

		return;
}

void CPolygon::Draw(HDC _hdc)
{
	// Create Pen & Brush
	HPEN hPen;
	HBRUSH hBrush;

	SetBkColor(_hdc, m_bgColor);
	SetBkMode(_hdc, m_bgMode);


	TempPoint.x = m_iEndX;
	TempPoint.y = m_iEndY;
	if (m_iStartX == m_iEndX && m_iStartY == m_iEndY)
	{
		AddPoint(TempPoint);
	}

	m_pPointList[m_nPoints] = TempPoint;

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

	//Draw Polygon
	Polygon(_hdc, m_pPointList, m_nPoints);

	DeleteObject(hPen);
	DeleteObject(hBrush);
	return;
}

