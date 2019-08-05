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

    // make arg parser
    argparse::ArgumentParser makeArgumentParser();

    // make argc, argv
    std::tuple<int, char**> input();
	char** newArgv(int count, ...);

    // start end callback
    void startQueryAPI();
	void endQueryAPI(int argc, char **argv);
    void printOutput();

private:
    std::thread m_runnerThread;


    //////////////////////////////////////////////////////////////////////////
    static std::unique_ptr<QueryAPI> m_instance;
    static std::once_flag m_onceFlag;

    QueryAPI() = default;
    QueryAPI(const QueryAPI &) = delete;
    QueryAPI &operator=(const QueryAPI &) = delete;
};
