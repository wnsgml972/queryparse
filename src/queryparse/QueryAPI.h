#pragma once
#include <tuple>

class QueryAPI
{
public:
	static void mainTestCode();

private:
	static char** newArgv(int count, ...);
	static std::tuple<int, char**> input();

	static void startQueryAPI();
	static void endQueryAPI(int argc, char **argv);
};
