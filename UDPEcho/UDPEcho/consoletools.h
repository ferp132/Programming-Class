//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//
#ifndef __CONSOLE_TOOLS_H__
#define __CONSOLE_TOOLS_H__

#include <iostream>
#include <ctype.h>
#include <conio.h>
//#include <Windows.h>

	char* GetLineFromConsole(char* pBuffer, int iNumChars);

	//namespace utility
	//{
		template <size_t iNumChars>
		inline char* GetLineFromConsole(char(&pBuffer)[iNumChars])
		{
			return GetLineFromConsole(pBuffer, (int)iNumChars);
		}
	//}

	char QueryOption(const char* Question, const char* Accepted, bool bCaseSensitive = false);

	char* CollapseBackspacesAndCleanInput(char* pBuffer);

	unsigned short QueryPortNumber(unsigned short uDefault = 0);




#endif // ifndef __CONSOLE_TOOLS_H__
