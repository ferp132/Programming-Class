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

//Global variables
HINSTANCE g_hInstance;
CCanvas* g_pCanvas;

IShape* g_pShape = 0;

HMENU g_hMenu;
int iPosX, iPosY;		// Mouse Position
COLORREF g_PenColor = RGB(0, 0, 0);		// Global Colour
int g_PenWidth = 1;			// Global Width
int g_PenStyle = PS_SOLID;
CHOOSECOLOR ColorPicker;
COLORREF customColors[16];

//bool Drawing = 0;


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


void GameLoop()
{
	//One frame of game logic occurs here...
}


ESHAPE CurrentTool;


LRESULT CALLBACK WindowProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{
	// This is the main message handler of the system.
	PAINTSTRUCT ps; // Used in WM_PAINT.
	HDC hdc;        // Handle to a device context.
	
	RECT rect;

	switch (_msg)
	{
	case WM_CREATE:
	{
		//initialization.
		g_pCanvas = new CCanvas();
		g_pCanvas->Initialise(_hwnd, 1500, 800);

		ColorPicker.lStructSize = sizeof(ColorPicker);
		ColorPicker.hwndOwner = _hwnd;
		ColorPicker.rgbResult = RGB(0, 0, 0);
		ColorPicker.lpCustColors = customColors;
		ColorPicker.Flags = CC_ANYCOLOR | CC_FULLOPEN;
		// Return Success.
		return (0);
	}
	break;
	case WM_RBUTTONDOWN:									
	{

		g_pShape = nullptr;
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
			}
			break;
			case LINESHAPE:									
			{
				g_pShape = new CLine(g_PenStyle, g_PenWidth, g_PenColor, iPosX, iPosY);
				g_pCanvas->AddShape(g_pShape);
				
				//If there is, Create an instance of it

			}
			break;
			default: break;
			}
			InvalidateRect(_hwnd, NULL, TRUE);

			return (0);
	}
	break;
	case WM_MOUSEMOVE:
	{
		iPosX = static_cast<int>(LOWORD(_lparam));
		iPosY = static_cast<int>(HIWORD(_lparam));
		
		
		// Test if left button is down...
		if (MK_LBUTTON)
		{
			if (g_pShape != nullptr/* && Drawing*/)
			{
				g_pShape->SetEndX(iPosX);
				g_pShape->SetEndY(iPosY);
				InvalidateRect(_hwnd, NULL, TRUE);
			}						
		}
			return (0);
	}
	break;
	case WM_LBUTTONUP:
	{
	//	Drawing = 0;
		g_pShape = nullptr;
	}
	break;
	/*case WM_LBUTTONDBLCLK:
	{
		Drawing = 0;
	}
break;*/
	case WM_PAINT:
	{
		hdc = BeginPaint(_hwnd, &ps);
		
		//Painting Code goes here:
	
		if (g_pCanvas != nullptr)
			g_pCanvas->Draw();

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
		case ID_FILE_EXIT:
		{
			PostQuitMessage(0);
			break;
		}
		case ID_HELP_ABOUT:
		{
			MessageBox(_hwnd, L"This paint tool was developed by .............", L"Author Information", MB_OK | MB_ICONINFORMATION);
			break;
		}
		case ID_SHAPE_LINE:
		{
			CurrentTool = LINESHAPE;
			break;
		}
		case ID_SHAPE_ELLIPSE:
		{
			CurrentTool = ELLIPSESHAPE;
			break;
		}
		case ID_FREEHAND:
		{
			CurrentTool = FREEHAND;
			break;
		}
		//PenWidth
		case ID_PEN_WIDTH_1:
		{
			g_PenWidth = 1;
			break;
		}
		case ID_PEN_WIDTH_2:
		{
			g_PenWidth = 2;
			break;
		}
		case ID_PEN_WIDTH_3:
		{
			g_PenWidth = 3;
			break;
		}
		case ID_PEN_WIDTH_4:
		{
			g_PenWidth = 4;
			break;
		}
		case ID_PEN_WIDTH_5:
		{
			g_PenWidth = 5;
			break;
		}
		case ID_PEN_COLOR:
		{
			
			if(ChooseColor(&ColorPicker)){
			g_PenColor = ColorPicker.rgbResult;
			}
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

		// Main game processing goes here.
		GameLoop(); //One frame of game logic occurs here...
	}

	// Return to Windows like this...
	return (static_cast<int>(msg.wParam));
}
