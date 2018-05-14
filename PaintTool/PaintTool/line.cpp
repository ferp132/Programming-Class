#include "line.h"

CLine::CLine(int _iStyle, int _iWidth, COLORREF _newColor, int _iStartX, int _iStartY)
{
	m_iStyle = _iStyle;
	m_iWidth = _iWidth;
	m_Color = _newColor;
	m_iStartX = _iStartX;
	m_iStartY = _iStartY;
}

CLine::CLine()
{
}

CLine::~CLine()
{
}

void CLine::Draw(HDC _hdc)
{
	HPEN hLinePen;
	hLinePen = CreatePen(m_iStyle, m_iWidth, m_Color);
	SelectObject(_hdc, hLinePen);

	MoveToEx(_hdc, m_iStartX, m_iStartY, NULL);
	LineTo(_hdc, m_iEndX, m_iEndY);

	DeleteObject(hLinePen);
}

void CLine::SetWidth(int _iNewWidth)
{
}
