#include "Logger.h"


Logger::Logger(LoggerLocation _location, Language language){
	location = _location;
	selectedLanguage = language;
}

Logger::~Logger() {

}

void Logger::Log(std::string message, bool endLine) {
	if (location == LoggerLocation::CONSOLE) {
		std::cout << message;
		if (endLine) {
			std::cout << std::endl;
		}
	}
}

void Logger::Log(Message message)
{
	switch (selectedLanguage) {
	case Language::ENGLISH:
		switch (message)
		{
		case Message::CAN_NOT_INITIALIZE_WINSOCK:
			Log("Can't initialize winsock! Quitting...");
			break;
		case Message::CAN_NOT_CREATE_SOCKET:
			Log("Can't create a socket! Quitting...");
			break;
		case Message::CLIENT_SOCKET_IS_INVALID:
			Log("Client Socket is invalid! Quitting...");
			break;
		case Message::SOCKET_ERROR_WHILE_RECIEVING_DATA:
			Log("Encountered socket error while recieving TCP data...");
			break;
		default:
			Log("Unknown Error");
		}
		break;
	default:
		Log("Undefined Language");
	}
}
