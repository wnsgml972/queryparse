#pragma once
#include "define.h"

namespace argparse
{
    class ArgumentParser;
}

// thread safe singleton
class QueryAPI
{
public:
    // instance
    static QueryAPI* GetInstance();

    // run API
    void runQueryAPI();


private:
    // main
    void queryAPI();

    // make argc, argv
    std::tuple<int, char**> inputString();
    char** makeArgv(int count, ...);

    // make arg parser
    std::shared_ptr<argparse::ArgumentParser> makeArgumentParser(const int& argc, char **dpArgv);
    void addPositionalArguments(std::shared_ptr<argparse::ArgumentParser> program, const int& argc);
    void addOptionalArguments(std::shared_ptr<argparse::ArgumentParser> program, const int& argc);

    // start end callback
    void startQueryAPI();
	void endQueryAPI(std::shared_ptr<argparse::ArgumentParser> program, const int& argc, char **dpArgv);
    void printOutput(std::shared_ptr<argparse::ArgumentParser> program);

    // printer
    void printer(std::wstring str);
    void printer(const char* str);

private:
    std::thread m_runnerThread;

    std::wstring m_inputString;
    std::vector<std::wstring> m_spiltedInputString;

    //////////////////////////////////////////////////////////////////////////
    static std::unique_ptr<QueryAPI> m_instance;
    static std::once_flag m_onceFlag;

    QueryAPI() = default;
    QueryAPI(const QueryAPI &) = delete;
    QueryAPI &operator=(const QueryAPI &) = delete;
};
