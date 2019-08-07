#pragma once
#include "BasePrinter.h"

namespace queryparse
{
    class ConsolePrinter : public BasePrinter
    {
    public:
        ConsolePrinter() = default;
        virtual ~ConsolePrinter() = default;

    private:
        virtual void messageOut(const std::wstring& str) override;
        void printBySTDConsold(const std::wstring& str);
    };
}
