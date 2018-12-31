#pragma once
#include <string>

enum struct LogColor_enum{
	Error, ErrorHighLight,Warning,WarningHighLight
};

void LogColorful(std::string,LogColor_enum);