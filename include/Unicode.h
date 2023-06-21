#ifndef UNICODE_H
#define UNICODE_H

#include <iostream>
#include <string>
#include <codecvt>
#include <locale>

#ifdef _WIN32
#include <fcntl.h>
#endif

#ifndef _WIN32
#include <clocale>
#endif

std::wstring convertWString(const std::string &narrowString);

#endif
