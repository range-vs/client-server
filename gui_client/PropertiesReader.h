#pragma once

#include <string>

#include "../shared/tinyxml2.h"

struct SocketData
{
	std::string address;
	std::string port;
};

class PropertiesReader
{
public:
	static SocketData readConfig(const std::string& path);
};