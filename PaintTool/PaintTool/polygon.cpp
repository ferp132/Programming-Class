#include "polygon.h"

CPolygon::CPolygon(EBRUSHSTYLE _iBrushStyle, int _iHatchStyle, COLORREF _FillColor, int _iPenStyle, int _iPenWidth, COLORREF _PenColor, int _X, int _Y)
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
	AddPoint(TempPoint);
	m_iEndX = TempPoint.x++;
	m_iEndY = TempPoint.y++;
	AddPoint(TempPoint);
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

	TempPoint.x = m_iEndX;
	TempPoint.y = m_iEndY;
	if (m_iStartX == m_iEndX && m_iStartY == m_iEndY)
	{
		AddPoint(TempPoint);
	}

	m_pPointList[m_nPoints-1] = TempPoint;

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

	//Draw Polygon
	Polygon(_hdc, m_pPointList, m_nPoints);

	DeleteObject(hPen);
	if (GetCurrentObject(_hdc, OBJ_BRUSH) == GetStockObject(NULL_BRUSH)) return;	// If the Brush is Hollow, Just return.
	else DeleteObject(hBrush);
	return;
}

