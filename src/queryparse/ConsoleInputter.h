#pragma once

#include "define.h"
#include "BaseInputter.h"

namespace queryparse
{
    // Based WString
    class ConsoleInputter : public BaseInputter
    {
    public:
        virtual std::wstring inputString() override;

    public:
        ConsoleInputter() = default;
        virtual ~ConsoleInputter() = default;
    };
}
