
#include "QueryAPI.h"
#include "define.h"
#include "argparse.hpp"
#include <stdarg.h>

void QueryAPI::mainTestCode()
{
	QueryAPI::startQueryAPI();

	const auto& [argc, argv] = QueryAPI::input();

	argparse::ArgumentParser program("queryparse");

	program.add_argument("square")
		.help("display the square of a given integer")
		.action([](const std::string& value) { return std::stoi(value); });

	try {
		program.parse_args(argc, argv);
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
		program.print_help();
		assert(0);
		exit(0);
	}

	auto input = program.get<int>("square");
	std::cout << (input * input) << std::endl;

	QueryAPI::endQueryAPI(argc, argv);
}

char** QueryAPI::newArgv(int count, ...)
{
	va_list args;
	int i;
	char **argv = (char **)malloc((count + 1) * sizeof(char*));
	char *temp;
	va_start(args, count);
	for (i = 0; i < count; i++) {
		temp = va_arg(args, char*);
		argv[i] = (char*)malloc(sizeof(temp) + 1);
		strcpy_s(argv[i], strlen(temp) + 1, temp);
	}
	argv[i] = NULL;
	va_end(args);

	return argv;
}

std::tuple<int, char**> QueryAPI::input()
{
	int argc = 2;
	auto argv = QueryAPI::newArgv(argc, "queryparse", "22");

	return { argc, argv };
}

void QueryAPI::startQueryAPI()
{
	std::cout << "Start Query Parse API" << std::endl;
}

void QueryAPI::endQueryAPI(int argc, char **argv)
{
	/* 메모리 해제 */
	free(argv);

	system("pause");
}