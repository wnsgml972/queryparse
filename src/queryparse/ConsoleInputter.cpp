
#include "ConsoleInputter.h"

std::wstring queryparse::ConsoleInputter::inputString()
{
    std::wstring str;
    getline(std::wcin, str);

    return str;
}