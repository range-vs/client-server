#pragma once

#include "Net.h"

public ref class HelpData
{
	System::String^ address;
	System::String^ port;
	NetPoint^ net;
	StringBuilderListening^ logger;

public:
	HelpData(System::String^ a, System::String^ p, NetPoint^ np, StringBuilderListening^ logger) : address(a), port(p), net(np), logger(logger) {}

	void ThreadProc()
	{
		net->StartSocket(address, port, logger);
	}
};

struct FindPair
{
	bool operator()(const std::pair<System::Boolean, unsigned>& p)
	{
		return p.first;
	}
};