#include "line.h"

CLine::CLine(int _iStyle, int _iWidth, COLORREF _newColor, int _iStartX, int _iStartY)
{

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
	LineTo(_hdc, 500, 250);

	DeleteObject(hLinePen);
}

void CLine::SetWidth(int _iNewWidth)
{
}
