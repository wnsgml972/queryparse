#pragma once

#include "define.h"

namespace queryparse
{
    // Based WString
    class BaseInputter
    {
    public:
        virtual std::wstring inputString() = 0;

    public:
        BaseInputter() = default;
        virtual ~BaseInputter() = default;

        std::tuple<int, char**> makeArgcArgv(const std::wstring& programName);


    protected:
        std::tuple<int, std::vector<std::wstring>> getArgcSpiltedInputStrings(const std::wstring& str, const std::wstring& programName);
        char** makeArgv(int count, const std::vector<std::wstring>& spiltedInputStrings);
        char** makeArgv(int count, ...);

    };
}
