#include "XmlDatabase.h"

XmlDatabase* XmlDatabase::instance(nullptr);

XmlDatabase* XmlDatabase::getInstance()
{
	if (!instance)
	{
		instance = new XmlDatabase();
		instance->LoadDatabase("configs/server/properties.xml");
	}
	return instance;
}


bool XmlDatabase::checkElement(const std::string& h)
{
	tinyxml2::XMLElement* xml_prop = xml_file->FirstChildElement("properties");
	tinyxml2::XMLElement* xml_hash = xml_prop->FirstChildElement("hashes");
	xml_hash = xml_hash->FirstChildElement("hash");
	if (!xml_hash)
		return false;
	if (h == xml_hash->Attribute("value"))
		return true;
	while (xml_hash)
	{
		xml_hash = xml_hash->NextSiblingElement("hash");
		if (!xml_hash)
			return false;
		if (h == xml_hash->Attribute("value"))
			return true;
	}
	return false;
}

void XmlDatabase::addElement(const std::string& h)
{
	tinyxml2::XMLElement* xml_prop = xml_file->FirstChildElement("properties");
	tinyxml2::XMLElement* xml_hash = xml_prop->FirstChildElement("hashes");
	tinyxml2::XMLElement* ne = xml_file->NewElement("hash");
	ne->SetAttribute("value", h.c_str());
	xml_hash->InsertEndChild(ne);
	xml_file->SaveFile("configs/server/properties.xml");
}

void XmlDatabase::deleteElement(const std::string& h)
{
	tinyxml2::XMLElement* xml_prop = xml_file->FirstChildElement("properties");
	tinyxml2::XMLElement* xml_hash = xml_prop->FirstChildElement("hashes");
	xml_hash = xml_hash->FirstChildElement("hash");
	if (!xml_hash)
		return;
	if (h == xml_hash->Attribute("value"))
		xml_file->DeleteNode(xml_hash);
	else
	{
		while (xml_hash)
		{
			xml_hash = xml_hash->NextSiblingElement("hash");
			if (!xml_hash)
				return;
			if (h == xml_hash->Attribute("value"))
			{
				xml_file->DeleteNode(xml_hash);
				break;
			}
		}
	}
	xml_file->SaveFile("configs/server/properties.xml");
}

std::string XmlDatabase::getPort()const
{
	return port;
}

void XmlDatabase::closeDatabase()
{
	delete xml_file; xml_file = nullptr;
	delete instance; instance = nullptr;
}

void XmlDatabase::LoadDatabase(const std::string& path)
{
	xml_file = new tinyxml2::XMLDocument();

	if (xml_file->LoadFile(path.c_str()) == tinyxml2::XMLError::XML_ERROR_FILE_NOT_FOUND)
	{
		// error
	}
	tinyxml2::XMLElement* xml_prop = xml_file->FirstChildElement("properties");
	port = xml_prop->Attribute("port");
}