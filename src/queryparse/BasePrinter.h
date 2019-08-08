#pragma once

#include "define.h"

namespace queryparse
{
    // Based WString
    class BasePrinter
    {
    public:
        virtual void messageOut(const std::wstring& str) = 0;

    public:
        BasePrinter() = default;
        virtual ~BasePrinter() = default;

        void print(const std::wstring& str);
        void print(const char* str);
    };
}
