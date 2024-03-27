#pragma once

#include "Pipe.h"
#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::string;

class Communication
{
public:
	Communication();
	~Communication();

	void SendMessege(const char* msg); //sends messege to the server
	string receiveMessege(); //receives the position from the engine



private:


	Pipe _pipe;
};
