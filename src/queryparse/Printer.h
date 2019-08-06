#pragma once

#include <string>

namespace queryparse
{
    class Printer
    {
    public:
        enum class PrinterType {
            STD_CONSOLE
        };

    public:
        Printer();
        virtual ~Printer() = default;

        void print(const std::wstring& str);
        void print(const char* str);

    private:
        std::wstring charPtr2WString(const char* str);

        PrinterType m_printerType;
    };
}
