#pragma once
#include <tuple>

class QueryAPI
{
public:
    static void runQueryAPI();


private:
    static void mainTestCode();
	static char** newArgv(int count, ...);
	static std::tuple<int, char**> input();
	static void startQueryAPI();
	static void endQueryAPI(int argc, char **argv);
};
