#pragma once
#include <string>
#include "LanguagesAndMessages.h"

class Messages
{
public:
	Messages(Language);
	~Messages();


	std::string Message(message);

private:
	Language selectedLanguage;
};
