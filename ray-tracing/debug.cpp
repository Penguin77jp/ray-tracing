#include <iostream>
#include <string>
#include <Windows.h>

#include "debug.h"


void LogColorful(std::string comment,LogColor_enum colorType) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	switch (colorType) {
	case LogColor_enum::Error:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
		break;
	case LogColor_enum::ErrorHighLight:
		SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY | BACKGROUND_RED);
		break;
	case LogColor_enum::Warning:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
		break;
	case LogColor_enum::WarningHighLight:
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_RED);
		break;
	}


	std::cout << comment << std::endl;

	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}