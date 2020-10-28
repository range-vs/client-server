#pragma once

#include <string>
#include <thread>

#include "Client.h"

public ref class NetPoint
{
	Client* cl;
public:
	void StartSocket(System::String^ p, System::String^ port, StringBuilderListening^ logger);
	void SendMessage(System::String^ m, const TYPE_OPERATION& tp);
	void StopSocket();
};

