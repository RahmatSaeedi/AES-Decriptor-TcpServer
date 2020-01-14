#pragma once
#include <iostream>
#include <string>
#include "LoggerLocations.h"
#include "Languages.h"
#include "Messages.h"


class Logger {
private:
	LoggerLocation location;
	Language selectedLanguage;
public:
	Logger(LoggerLocation = LoggerLocation::CONSOLE, Language = Language::ENGLISH);
	void Log(std::string, bool endLine = true);
	void Log(Message);
	~Logger();
};