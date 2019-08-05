
#include "QueryAPI.h"
#include "argparse.hpp"
#include <stdarg.h>

// static initialize
std::unique_ptr<QueryAPI> QueryAPI::m_instance = {};
std::once_flag QueryAPI::m_onceFlag = {};


QueryAPI* QueryAPI::GetInstance()
{
    std::call_once(QueryAPI::m_onceFlag, [&]() {
        m_instance.reset(new QueryAPI());
        });


    return m_instance.get();
}

void QueryAPI::runQueryAPI()
{
    m_runnerThread = std::thread([&]()
    {
        queryAPI();
    });

    m_runnerThread.join();
}



//////////////////////////////////////////////////////////////////////////
void QueryAPI::queryAPI()
{
	startQueryAPI();

    // parse
    auto program = makeArgumentParser();
    const auto&[argc, argv] = input();
    try 
    {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) 
    {       
        if (!(strcmp("help called", err.what()) == 0))
        {
            std::cout << err.what() << std::endl << std::endl;
            program.print_help();
            assert(0);
            exit(0);
        }
        else
        {
            program.print_help();
        }
    }	

	endQueryAPI(argc, argv);
}

argparse::ArgumentParser QueryAPI::makeArgumentParser()
{
    argparse::ArgumentParser program("queryparse");

    // add args
    {
        program.add_argument("square")
            .help("display the square of a given integer")
            .action([](const std::string& value) { return std::stoi(value); });

        program.add_argument("--verbose")
            .default_value(false)
            .implicit_value(true);

        program.add_argument("integer")
            .help("Input number")
            .action([](const std::string& value) { return std::stoi(value); });

        program.add_argument("floats")
            .help("Vector of floats")
            .nargs(4)
            .action([](const std::string& value) { return std::stof(value); });

        program.add_argument("--input_files")
            .help("The list of input files")
            .nargs(2);

        program.add_argument("--query_point")
            .help("3D query point")
            .nargs(3)
            .default_value(std::vector<double>{0.0, 0.0, 0.0})
            .action([](const std::string& value) { return std::stod(value); });
    }

    return program;
}

std::tuple<int, char**> QueryAPI::input()
{
    std::string programName("queryparse");
    int argc = 2;
    auto argv = newArgv(argc, programName.c_str(), "--help");

    return { argc, argv };
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


void QueryAPI::startQueryAPI()
{
	std::cout << "Start Query Parse API" << std::endl;
}

void QueryAPI::endQueryAPI(int argc, char **argv)
{
    printOutput();

	free(argv);
}

void QueryAPI::printOutput()
{
    //1.
    //         auto input = program.get<int>("square");
    //         if (program["--verbose"] == true)
    //         {
    //             std::cout << "The square of " << input << " is " << (input * input) << std::endl;
    //         }
    //         else
    //         {
    //             std::cout << (input * input) << std::endl;
    //         }
    //
    //2.
    //         auto files = program.get<std::list<std::string>>("--input_files");
    //
    //3.
    //    auto query_point = program.get<std::vector<double>>("--query_point");  // {3.5, 4.7, 9.2}
}
