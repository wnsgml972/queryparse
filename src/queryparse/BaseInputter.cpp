
#include "BaseInputter.h"
#include <stdarg.h>

std::tuple<int, char**> queryparse::BaseInputter::makeArgcArgv(const std::wstring& programName)
{
    const auto& input = inputString();
    const auto& [argc, argv] = getArgcArgvByInputString(input, programName);

    char** dpArgv = makeArgv(argc, argv);

    return { argc, dpArgv };
}

std::vector<std::wstring> queryparse::BaseInputter::getSpiltedInputStrings(const std::wstring& str)
{
    std::vector<std::wstring> spiltedInputStrings;

    std::wstringstream sStream(str);
    std::wstring item;
    std::wstring delimiterChar(L" ");

    while (std::getline(sStream, item, delimiterChar.c_str()[0]))
    {
        spiltedInputStrings.push_back(item);
    }
    return spiltedInputStrings;
}

std::tuple<int, std::vector<std::wstring>> queryparse::BaseInputter::getArgcArgvByInputString(const std::wstring& str, const std::wstring& programName)
{
    std::vector<std::wstring> argv;
    
    // 1. Add Program Name
    {
        argv.push_back(programName);
    }

    // 2. Spilt String
    {
        const auto& spiltedInputStrings = getSpiltedInputStrings(str);

        for (auto spiltedInputString : spiltedInputStrings)
        {
            argv.push_back(spiltedInputString);
        }
    }

    return { argv.size(), argv };
}

char** queryparse::BaseInputter::makeArgv(int count, ...)
{
    va_list args;
    int i;
    char **dpArgv = (char **)malloc((count + 1) * sizeof(char*));
    char *pTemp;

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
    char *pTemp{};
    int i{};
    char **dpArgv = (char **)malloc((count + 1) * sizeof(char*));
    
    for (i = 0; i < count; i++) 
    {
        std::string str = StringConverter::wstring2string(spiltedInputStrings[i]);
        pTemp = (char *)str.c_str(); // 여기서 올바른 변환 해야할 듯?
        dpArgv[i] = (char*)malloc(sizeof(pTemp) + 1);
        strcpy_s(dpArgv[i], strlen(pTemp) + 1, pTemp);
    }
    dpArgv[i] = NULL;

    return dpArgv;
}