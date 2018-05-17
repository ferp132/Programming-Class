#include "canvas.h"
#include "backBuffer.h"
#include "shape.h"

CCanvas::CCanvas()
{
	m_pBackBuffer = new CBackBuffer();
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
	//hwnd = _hwnd;

	m_pBackBuffer->Initialise(_hwnd, _iWidth, _iHeight);

	// m_pBackBuffer->Clear();

	return true;
}

CBackBuffer * CCanvas::GetBackBuffer()
{
	return m_pBackBuffer;
}

bool CCanvas::Draw()
{
	//HDC hdc = GetDC(hwnd);

	m_pBackBuffer->Clear();

	// Draw here
	for (IShape * shape : m_shapes)
	{
		shape->Draw(m_pBackBuffer->GetBFDC());
	}

	m_pBackBuffer->Present();

	//ReleaseDC(hwnd, hdc);

	return true;
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
