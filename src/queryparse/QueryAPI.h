#pragma once
#include "define.h"

class QueryAPI
{
public:
    static QueryAPI* GetInstance();
    void runQueryAPI();



private:
    void mainTestCode();
    void printOutput();
	char** newArgv(int count, ...);
	std::tuple<int, char**> input();
	void startQueryAPI();
	void endQueryAPI(int argc, char **argv);

private:
    std::thread m_runnerThread;


    //////////////////////////////////////////////////////////////////////////
    static std::unique_ptr<QueryAPI> m_instance;
    static std::once_flag m_onceFlag;

    QueryAPI() = default;
    QueryAPI(const QueryAPI &) = delete;
    QueryAPI &operator=(const QueryAPI &) = delete;
};
