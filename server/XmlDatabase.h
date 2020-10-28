#pragma once

#include <string>

#include "../shared/tinyxml2.h"

class XmlDatabase
{
	tinyxml2::XMLDocument* xml_file;
	static XmlDatabase* instance;

	XmlDatabase(){}
	XmlDatabase(const XmlDatabase&) = delete;
	XmlDatabase& operator=(const XmlDatabase&) = delete;

	std::string port;

	void LoadDatabase(const std::string& path);


public:
	static XmlDatabase* getInstance();

	bool checkElement(const std::string& h);

	void addElement(const std::string& h);

	void deleteElement(const std::string& h);

	std::string getPort()const;

	void closeDatabase();
};

