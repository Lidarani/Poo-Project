#include<Unicode.h>

std::wstring convertWString(const std::string narrowString){
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	return converter.from_bytes(narrowString);
};