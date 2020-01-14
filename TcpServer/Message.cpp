#include "Messages.h"


Messages::Messages(Language language)
{
	selectedLanguage = language;
}

Messages::~Messages()
{

}

std::string Messages::Message(message m) {
	switch (selectedLanguage) {
	case Language::ENGLISH:
		switch (m)
		{
		case message::CAN_NOT_INITIALIZE_WINSOCK:
			return "Can't initialize winsock! Quitting...";
			break;
		case message::CAN_NOT_CREATE_SOCKET:
			return "Can't create a socket! Quitting...";
			break;
		case message::CLIENT_SOCKET_IS_INVALID:
			return "Client Socket is invalid! Quitting...";
			break;
		default:
			return "Unknown Error";
		}
		break;
	default:
		return "Undefined Language";
	}
}