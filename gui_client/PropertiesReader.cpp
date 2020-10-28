#include "PropertiesReader.h"

SocketData PropertiesReader::readConfig(const std::string& path)
{
	SocketData data;
	tinyxml2::XMLDocument* xml_file = new tinyxml2::XMLDocument();

	if (xml_file->LoadFile(path.c_str()) == tinyxml2::XMLError::XML_ERROR_FILE_NOT_FOUND)
	{
		// error
	}
	tinyxml2::XMLElement* xml_prop = xml_file->FirstChildElement("properties");
	data.address = xml_prop->Attribute("address");
	data.port = xml_prop->Attribute("port");
	delete xml_file;
	return data;
}