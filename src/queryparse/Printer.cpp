
#include "Printer.h"
#include <string>
#include <iostream>


queryparse::Printer::Printer()
{
    m_printerType = PrinterType::STD_CONSOLE;
}

void queryparse::Printer::print(const std::wstring& str)
{
    std::wcout << str.c_str() << std::endl;
}

void queryparse::Printer::print(const char* str)
{
    const auto& wstr = charPtr2WString(str);
    print(wstr);
}

std::wstring queryparse::Printer::charPtr2WString(const char* str)
{
    size_t cn;
    auto len = static_cast<int>(strlen(str));
    std::wstring wstr(L' ', len + 1);
    mbstowcs_s(&cn, &wstr[0], len + 1, str, len + 1);

    return wstr;
}
