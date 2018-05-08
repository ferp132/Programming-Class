#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _iCmdShow){

	MessageBox(NULL, L"Simple Program MMMMKAAAAY ", L"First Windows Program ever", MB_RETRYCANCEL | MB_ICONINFORMATION);

	return (0);
}