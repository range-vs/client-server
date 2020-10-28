#include "FileReader.h"
#include "ConverterString.h"

System::String^ FileReader::OpenFile()
{
	System::String^ path = nullptr;
	OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
	if (openFileDialog->ShowDialog())
		path = openFileDialog->FileName;
	return path;
}

std::string FileReader::ReadFile(System::String^ path)
{
	std::string inputFile = ConverterString::toString(path);
	std::ifstream inFile(inputFile, std::ios_base::binary);

	inFile.seekg(0, std::ios_base::end);
	size_t length = inFile.tellg();
	inFile.seekg(0, std::ios_base::beg);
	std::string buffer;
	buffer.reserve(length);
	std::copy(std::istreambuf_iterator<char>(inFile),
		std::istreambuf_iterator<char>(),
		std::back_inserter(buffer));
	return buffer;
}

std::string FileReader::CalculateHash(const std::string& arrBytes)
{
	std::string output = sha256(arrBytes);
	return output;
}