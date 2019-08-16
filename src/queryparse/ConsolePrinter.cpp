
#include "ConsolePrinter.h"
#include <string>
#include <iostream>

void queryparse::ConsolePrinter::messageOut(const std::wstring& str)
{
    std::wcout << str.c_str() << std::endl;
}
