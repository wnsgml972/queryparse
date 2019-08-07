
#include "BasePrinter.h"
#include <iostream>


void queryparse::BasePrinter::print(const std::wstring& str)
{
    messageOut(str);
}

void queryparse::BasePrinter::print(const char* str)
{
    const auto& wstr = charPtr2WString(str);
    print(wstr);
}

std::wstring queryparse::BasePrinter::charPtr2WString(const char* str)
{
    size_t cn;
    auto len = static_cast<int>(strlen(str));
    std::wstring wstr(L' ', len + 1);
    mbstowcs_s(&cn, &wstr[0], len + 1, str, len + 1);

    return wstr;
}
