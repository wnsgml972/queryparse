
#include "BasePrinter.h"

void queryparse::BasePrinter::print(const std::wstring& str)
{
    messageOut(str);
}

void queryparse::BasePrinter::print(const char* str)
{
    auto wstr = StringConverter::charPtr2wstring(str);
    print(wstr);
}
