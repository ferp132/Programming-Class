#define WIN32_LEAN_AND_MEAN

#include <windows.h>																					//Include all the windows headers
#include <windowsx.h>																					//Include usefull macros

#define WINDOW_CLASS_NAME L"WINCLASS1"

LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam){

	//This is the main message handler of the system.
	PAINTSTRUCT ps;																						//Used in WM_Paint
	HDC hdc;																							//Handle to a device context

	//What is the message?
	switch (_msg)
	{
	case WM_CREATE:
	{
		//Do initialisation stuff here

		//Return Success
		return (0);
	}
	break;

	case WM_PAINT:
	{
		// Simply Validate the Window
		hdc = BeginPaint(_hwnd, &ps);

		//You would do all your painting here...

		EndPaint(_hwnd, &ps);

		// Return Success
		return(0);
	}
	break;

	case WM_DESTROY:
	{
		//Kill the application, this sends a WM_QUIT message.
		PostQuitMessage(0);

		//Return Success.
		return(0);
	}
	break;

	default:break;
	} //End Switch.

	//Proocess any messages that we did not take care of...

	return (DefWindowProc(_hwnd, _msg, _wparam, _lparam));
}

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow)
{
	WNDCLASSEX winclass;																				//THis will hold the class we create.
	HWND hwnd;																							//Generic Window Handle
	MSG msg;																							//Generic Message.

	//First fill in the eindow class structure.
	winclass.cbSize			= sizeof(WNDCLASSEX);
	winclass.style			= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc	= WindowProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= _hInstance;
	winclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground	= static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	winclass.lpszMenuName	= NULL;
	winclass.lpszClassName	= WINDOW_CLASS_NAME;
	winclass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);

	//register the window class
	if (!RegisterClassEx(&winclass))
	{
		return(0);
	}

	hwnd = CreateWindowEx(	NULL,								// Extended Style.
							WINDOW_CLASS_NAME,					// Class
							L"Your Basic Window",				// Title
							WS_OVERLAPPEDWINDOW | WS_VISIBLE,
							0, 0,								// Initial x,y.
							400, 400,							// initial width, height.
							NULL,								//Handle to parent.
							NULL,								// Handle to menu.
							_hInstance,							// INtance of this application
							NULL);								//Extra creation parameters

	//Check the window was created successfully.
	if (!hwnd)
	{
		return(0);
	}

	//Enter main event loop.
	while ((GetMessage(&msg, NULL, 0, 0)) > 0)
	{
		// Translate any accelerator keys...
		TranslateMessage(&msg);

		// Send the message to te window proc.
		DispatchMessage(&msg);
	}

	//Return to windows like this...
	return (static_cast<int>(msg.wParam));
}