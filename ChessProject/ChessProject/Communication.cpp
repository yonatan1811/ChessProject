#include "Communication.h"


Communication::Communication()
{
	bool connect = _pipe.connect();

	while (!connect)
	{
		connect = _pipe.connect();
		Sleep(5000);
	}
}

Communication::~Communication()
{
	_pipe.close();
}


void Communication::SendMessege(const char* msg) //sends messege to the server
{
	_pipe.sendMessageToGraphics(msg);
}

string Communication::receiveMessege() //receives the position from the engine
{
	return _pipe.getMessageFromGraphics();
}