#include "canvas.h"
#include "shape.h"

CCanvas::CCanvas()
{
}

CCanvas::~CCanvas()
{
	for (int i = 0; i < m_shapes.size(); i++)
	{
		delete m_shapes.at(i);
	}
}

bool CCanvas::Initialise(HWND _hwnd, int _iWidth, int _iHeight)
{
	hwnd = _hwnd;
	return false;
}

CBackBuffer * CCanvas::GetBackBuffer()
{
	return nullptr;
}

bool CCanvas::Draw()
{
	HDC hdc = GetDC(hwnd);

	// Draw here
	for (IShape * shape : m_shapes)
	{
		shape->Draw(hdc);
	}

	ReleaseDC(hwnd, hdc);

	return false;
}

void CCanvas::Save(HWND _hwnd)
{
}

void CCanvas::AddShape(IShape * shape)
{
	m_shapes.push_back(shape);
}

void CCanvas::AddStamp(CStamp *)
{
}
