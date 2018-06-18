/***********************
  Bachelor of Software Engineering
  Media Design School
  Auckland
  New Zealand

  (c) 2018 Media Design School

  File Name   :   [Filename]
  Description :   [One line description of what is the file is for]
  Author      :   Louis Cresswell
  Mail        :   louis.cresswell@mediadesign.school.nz
********************/

//#define WIN32_LEAN_AND_MEAN


//TODO: Create Draw Functions FOr Ellipse and Rectangle
//		Create MENUCHECKER FUNCTION
//		CREATE POLYGON TOOL


#include <windows.h>   // Include all the windows headers.
#include <windowsx.h>  // Include useful macros.

#include "resource.h"
#include "shape.h"
#include "line.h"
#include "canvas.h"
#include "rectangle.h"
#include "ellipse.h"
#include "polygon.h"
#include "stamp.h"
#include "backBuffer.h"


#define WINDOW_CLASS_NAME L"WINCLASS1"

//Enum to decalre the type of tool supported by the application.
enum ESHAPE
{
	FREEHAND = 0,
	LINESHAPE,
	RECTANGLESHAPE,
	ELLIPSESHAPE,
	POLYGONSHAPE,
	STAMP
};

//Global variables
HINSTANCE g_hInstance;
CCanvas* g_pCanvas = nullptr;

IShape* g_pShape = nullptr;
HMENU g_hMenu;

int iPosX, iPosY;							// Mouse Position

COLORREF g_PenColor = RGB(0, 0, 0);			// Pen Colour
COLORREF g_BrushColor = RGB(255, 255, 255);		// Brush Colour

int g_PenWidth = 1;							// Line Width

int g_PenStyle = PS_SOLID;					// Pen Style
int g_HatchStyle = HS_CROSS;				// Hatch Style
EBRUSHSTYLE g_BrushStyle = SOLID;			// Brush Style

CHOOSECOLOR ColorPicker;					// For Colour Picker Dialog
COLORREF customColors[16];					// ""

COLORREF g_bgColor;
int g_bgMode = TRANSPARENT;
RECT rect;


ESHAPE CurrentTool;							// Stores current tool being used

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

void GameLoop()
{
	if (g_pCanvas != nullptr)
	{
		g_pCanvas->Draw();
	}
}

LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	PAINTSTRUCT ps; // Used in WM_PAINT.
	HDC hdc;        // Handle to a device context.
	HMENU hmenu = GetMenu(_hwnd);

//	RECT rect;

	switch (_msg)
	{
	case WM_CREATE:
	{
		//initialisation of canvas
		g_pCanvas = new CCanvas();
		GetClientRect(_hwnd, &rect);
		g_pCanvas->Initialise(_hwnd, 1500, 800);

		//initialisation of colour picker
		ColorPicker.lStructSize = sizeof(ColorPicker);
		ColorPicker.hwndOwner = _hwnd;
		ColorPicker.rgbResult = RGB(0, 0, 0);
		ColorPicker.lpCustColors = customColors;
		ColorPicker.Flags = CC_ANYCOLOR | CC_FULLOPEN;

		g_hMenu = GetMenu(_hwnd); // menu handle

		// Return Success.
		return (0);
	}
	break;
	case WM_LBUTTONDOWN:									// when the left button is pressed
	{
		iPosX = static_cast<int>(LOWORD(_lparam));			// find the pointer location
		iPosY = static_cast<int>(HIWORD(_lparam));
			switch (CurrentTool)							// find the current shape
			{
			case FREEHAND:
			{
				return(0);									// If there is no shape, do nothing
				break;
			}
			case LINESHAPE:									
			{
				if (g_pShape == nullptr)
				{
					g_pShape = new CLine(g_PenStyle, g_PenWidth, g_PenColor, iPosX, iPosY, g_bgColor, g_bgMode);  //Create A New Line and add it to the canvas
					g_pCanvas->AddShape(g_pShape);
					
				}
				break;
				
			}
			case RECTANGLESHAPE:
			{
				if (g_pShape == nullptr)
				{
					g_pShape = new CRectangle(g_BrushStyle, g_HatchStyle, g_BrushColor, g_PenStyle, g_PenWidth, g_PenColor, iPosX, iPosY, g_bgColor, g_bgMode);
					g_pCanvas->AddShape(g_pShape);
					break;
				}
				break;
			}
			case ELLIPSESHAPE:
			{
				if (g_pShape == nullptr)
				{
					g_pShape = new CEllipse(g_BrushStyle, g_HatchStyle, g_BrushColor, g_PenStyle, g_PenWidth, g_PenColor, iPosX, iPosY, g_bgColor, g_bgMode);
					g_pCanvas->AddShape(g_pShape);
					break;
				}
				break;
			}
			case POLYGONSHAPE:
			{
				if (g_pShape != nullptr)
				{
					g_pShape->SetStartX(iPosX);
					g_pShape->SetStartY(iPosY);
				}
				if (g_pShape == nullptr)
				{
					g_pShape = new CPolygon(g_BrushStyle, g_HatchStyle, g_BrushColor, g_PenStyle, g_PenWidth, g_PenColor, iPosX, iPosY, g_bgColor, g_bgMode);
					g_pCanvas->AddShape(g_pShape);
				}
				break;
			}
			default: break;
			}	
			
			break;
	}
	case WM_MOUSEMOVE:
	{
		iPosX = static_cast<int>(LOWORD(_lparam));
		iPosY = static_cast<int>(HIWORD(_lparam));

		// Test if left button is down...
		if (MK_LBUTTON)
		{
			if (g_pShape != nullptr)
			{
				g_pShape->SetEndX(iPosX);
				g_pShape->SetEndY(iPosY);
				// InvalidateRect(_hwnd, NULL, TRUE);
			}						
		}
		return (0);
	}
	break;

	case WM_LBUTTONUP:
	{
		if(CurrentTool != POLYGONSHAPE) 
			g_pShape = nullptr;
		break;
	}
	case WM_RBUTTONDOWN:
	{
		if (CurrentTool == POLYGONSHAPE) 
		{
			g_pShape = nullptr;
		}
		break;
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(_hwnd, &ps);
		
		//Painting Code goes here:
	
		/*if (g_pCanvas != nullptr)
			g_pCanvas->Draw();*/

		EndPaint(_hwnd, &ps);
		// Return Success.
		return (0);
	}
	break;
	//All the Menu item ID's Go Here
	case WM_COMMAND:
	{

		switch (LOWORD(_wparam))
		{
		//File
		case ID_FILE_SAVE:
		{
			break;
		}
		case ID_FILE_OPEN:
		{
			break;
		}
		case ID_FILE_EXIT:
		{
			PostQuitMessage(0);
			break;
		}
		//Shape
		case ID_FREEHAND:
		{
			CurrentTool = FREEHAND;
			break;
		}
		case ID_SHAPE_LINE:
		{
			CurrentTool = LINESHAPE;
			CheckMenuRadioItem(hmenu, ID_SHAPE_LINE, ID_SHAPE_POLYGON, ID_SHAPE_LINE, MF_BYCOMMAND);
			break;
		}
		case ID_SHAPE_R:
		{
			CurrentTool = RECTANGLESHAPE;
			CheckMenuRadioItem(hmenu, ID_SHAPE_LINE, ID_SHAPE_POLYGON, ID_SHAPE_R, MF_BYCOMMAND);
			break;
		}
		case ID_SHAPE_ELLIPSE:
		{
			CurrentTool = ELLIPSESHAPE;
			CheckMenuRadioItem(hmenu, ID_SHAPE_LINE, ID_SHAPE_POLYGON, ID_SHAPE_ELLIPSE, MF_BYCOMMAND);
			break;
		}
		case ID_SHAPE_POLYGON:
		{
			CurrentTool = POLYGONSHAPE;
			CheckMenuRadioItem(hmenu, ID_SHAPE_LINE, ID_SHAPE_POLYGON, ID_SHAPE_POLYGON, MF_BYCOMMAND);
			break;
		}
		//Pen
		//Width
		case ID_PEN_WIDTH_1:
		{

			CheckMenuRadioItem(hmenu, ID_PEN_WIDTH_1, ID_PEN_WIDTH_5, ID_PEN_WIDTH_1, MF_BYCOMMAND);
			g_PenWidth = 1;
			break;
		}
		case ID_PEN_WIDTH_2:
		{
			CheckMenuRadioItem(hmenu, ID_PEN_WIDTH_1, ID_PEN_WIDTH_5, ID_PEN_WIDTH_2, MF_BYCOMMAND);
			g_PenWidth = 2;
			break;
		}
		case ID_PEN_WIDTH_3:
		{
			CheckMenuRadioItem(hmenu, ID_PEN_WIDTH_1, ID_PEN_WIDTH_5, ID_PEN_WIDTH_3, MF_BYCOMMAND);
			g_PenWidth = 3;
			break;
		}
		case ID_PEN_WIDTH_4:
		{
			CheckMenuRadioItem(hmenu, ID_PEN_WIDTH_1, ID_PEN_WIDTH_5, ID_PEN_WIDTH_4, MF_BYCOMMAND);
			g_PenWidth = 4;
			break;
		}
		case ID_PEN_WIDTH_5:
		{
			CheckMenuRadioItem(hmenu, ID_PEN_WIDTH_1, ID_PEN_WIDTH_5, ID_PEN_WIDTH_5, MF_BYCOMMAND);
			g_PenWidth = 5;
			break;
		}
		//Colour
		case ID_PEN_COLOR:
		{
			if(ChooseColor(&ColorPicker)){
			g_PenColor = ColorPicker.rgbResult;
			}
			break;
		}
		//Style
		case ID_PEN_STYLE_SOLID:
		{
			CheckMenuRadioItem(hmenu, ID_PEN_STYLE_SOLID, ID_PEN_STYLE_DASHDOT, ID_PEN_STYLE_SOLID, MF_BYCOMMAND);
			g_PenStyle = PS_SOLID;
			break;
		}
		case ID_PEN_STYLE_DOT:
		{
			CheckMenuRadioItem(hmenu, ID_PEN_STYLE_SOLID, ID_PEN_STYLE_DASHDOT, ID_PEN_STYLE_DOT, MF_BYCOMMAND);
			g_PenStyle = PS_DOT;
			break;
		}
		case ID_PEN_STYLE_DASH:
		{
			CheckMenuRadioItem(hmenu, ID_PEN_STYLE_SOLID, ID_PEN_STYLE_DASHDOT, ID_PEN_STYLE_DASH, MF_BYCOMMAND);
			g_PenStyle = PS_DASH;
			break;
		}
		case ID_PEN_STYLE_DASHDOT:
		{
			CheckMenuRadioItem(hmenu, ID_PEN_STYLE_SOLID, ID_PEN_STYLE_DASHDOT, ID_PEN_STYLE_DASHDOT, MF_BYCOMMAND);
			g_PenStyle = PS_DASHDOT;
			break;
		}
		//Brush
		//Colour
		case ID_BRUSH_COLOR:
		{
			if (ChooseColor(&ColorPicker)) {
				g_BrushColor = ColorPicker.rgbResult;
			}
		break;
		}
		case ID_BRUSH_STYLE_SOLID:
		{
			CheckMenuRadioItem(hmenu, ID_BRUSH_STYLE_SOLID, ID_BRUSH_STYLE_CROSSHATCH, ID_BRUSH_STYLE_SOLID, MF_BYCOMMAND);
			g_BrushStyle = SOLID;
			break;
		}
		case ID_BRUSH_STYLE_HATCH:
		{
			CheckMenuRadioItem(hmenu, ID_BRUSH_STYLE_SOLID, ID_BRUSH_STYLE_CROSSHATCH, ID_BRUSH_STYLE_HATCH, MF_BYCOMMAND);
			g_BrushStyle = HATCH;
			g_HatchStyle = HS_DIAGCROSS;
			break;
		}
		case ID_BRUSH_STYLE_CROSSHATCH:
		{
			CheckMenuRadioItem(hmenu, ID_BRUSH_STYLE_SOLID, ID_BRUSH_STYLE_CROSSHATCH, ID_BRUSH_STYLE_CROSSHATCH, MF_BYCOMMAND);
			g_BrushStyle = HATCH;
			g_HatchStyle = HS_CROSS;
			break;
		}
		//Background
		case ID_BACKGROUND_COLOUR:
		{
			if (ChooseColor(&ColorPicker)) {
				g_bgColor = ColorPicker.rgbResult;
			}
		break;
		}
		case ID_BACKGROUND_OPAQUE:
		{
			g_bgMode = OPAQUE;
		break;
		}
		case ID_BACKGROUND_TRANSPARENT:
		{
			g_bgMode = TRANSPARENT;
		break;
		}
		//Help
		case ID_HELP_ABOUT:
		{
			MessageBox(_hwnd, L"This paint tool was developed by .............", L"Author Information", MB_OK | MB_ICONINFORMATION);
			break;
		}
		default:
			break;
		}
		return(0);
	}
	break;
	case WM_DESTROY:
	{
		delete g_pCanvas;
		g_pCanvas = nullptr;

		// Kill the application, this sends a WM_QUIT message.
		PostQuitMessage(0);

		// Return success.
		return (0);
	}
	break;

		default:break;
	} // End switch.

	  // Process any messages that we did not take care of...
	return (DefWindowProc(_hwnd, _msg, _wparam, _lparam));
}

int WINAPI WinMain(HINSTANCE _hInstance,
	HINSTANCE _hPrevInstance,
	LPSTR _lpCmdLine,
	int _nCmdShow)
{
	WNDCLASSEX winclass; // This will hold the class we create.
	HWND hwnd;           // Generic window handle.
	MSG msg;             // Generic message.

	g_hInstance = _hInstance;
	// First fill in the window class structure.
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground =
		static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register the window class
	if (!RegisterClassEx(&winclass))
	{
		return (0);
	}

	g_hMenu = LoadMenu(_hInstance, MAKEINTRESOURCE(IDR_MENU1));
	// create the window
	hwnd = CreateWindowEx(NULL, // Extended style.
		WINDOW_CLASS_NAME,      // Class.
		L"My Paint Tool",   // Title.
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		100, 100,                    // Initial x,y.
		1500, 800,                // Initial width, height.
		NULL,                   // Handle to parent.
		g_hMenu,                   // Handle to menu.
		_hInstance,             // Instance of this application.
		NULL);                  // Extra creation parameters.

	if (!(hwnd))
	{
		return (0);
	}



	// Enter main event loop
	while (true)
	{
		// Test if there is a message in queue, if so get it.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Test if this is a quit.
			if (msg.message == WM_QUIT)
			{
				break;
			}

			// Translate any accelerator keys.
			TranslateMessage(&msg);
			// Send the message to the window proc.
			DispatchMessage(&msg);
		}
		GameLoop();
	}
	// Return to Windows like this...
	return (static_cast<int>(msg.wParam));
}
