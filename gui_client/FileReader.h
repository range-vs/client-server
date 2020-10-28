#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "../shared/sha256.h"

using namespace Microsoft::Win32;
using namespace System::Windows;

public ref class FileReader
{
public:
	static System::String^ OpenFile();

	static std::string ReadFile(System::String^ path);

	static std::string CalculateHash(const std::string& arrBytes);

};
