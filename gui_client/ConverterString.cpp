#include "ConverterString.h"

std::string ConverterString::toString(const std::wstring& s)
{
	return converter.to_bytes(s.c_str());
}

std::string ConverterString::toString(const wchar_t* s)
{
	return converter.to_bytes(s);
}

std::wstring ConverterString::toWString(const std::string& s)
{
	return converter.from_bytes(s.c_str());
}

std::wstring ConverterString::toWString(const char* s)
{
	return converter.from_bytes(s);
}

std::string ConverterString::toString(System::String^ s)
{
	const char* chars = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(s)).ToPointer();
	std::string out(chars);
	System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr((void*)chars));
	return out;
}

std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> ConverterString::converter;