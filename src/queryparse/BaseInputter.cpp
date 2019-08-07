
#include "BaseInputter.h"
#include <stdarg.h>

std::tuple<int, char**> queryparse::BaseInputter::makeArgcArgv(const std::wstring& programName)
{
    const auto& str = inputString();
    auto[argc, spiltedInputStrings] = getArgcSpiltedInputStrings(str);

    auto dpArgvTemp = makeArgv(argc, programName.c_str(), "--help", "-3", "-3", "-3");
    auto dpArgv = makeArgv(argc, programName.c_str(), spiltedInputStrings);

    return { argc, dpArgv };
}

std::tuple<int, std::vector<std::wstring>> queryparse::BaseInputter::getArgcSpiltedInputStrings(const std::wstring& str)
{
    return { 5, {} };
}

char** queryparse::BaseInputter::makeArgv(int count, ...)
{
    va_list args{};
    int i{};
    char **dpArgv = (char **)malloc((count + 1) * sizeof(char*));
    char *pTemp{};

    {
        va_start(args, count);
        for (i = 0; i < count; i++) {
            pTemp = va_arg(args, char*);
            dpArgv[i] = (char*)malloc(sizeof(pTemp) + 1);
            strcpy_s(dpArgv[i], strlen(pTemp) + 1, pTemp);
        }
        dpArgv[i] = NULL;
        va_end(args);
    }


    return dpArgv;
}

char** queryparse::BaseInputter::makeArgv(int count, const std::vector<std::wstring>& spiltedInputStrings)
{
    va_list args{};
    int i{};
    char **dpArgv = (char **)malloc((count + 1) * sizeof(char*));
    char *pTemp{};


    return dpArgv;
}