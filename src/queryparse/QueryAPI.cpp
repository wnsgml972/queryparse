
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
    using namespace std::literals;

    m_runnerThread = std::thread([&]()
    {
        while (1)
        {
            queryAPI();
            std::this_thread::sleep_for(1ms);
        }
    });

    m_runnerThread.join();
}



//////////////////////////////////////////////////////////////////////////
void QueryAPI::queryAPI()
{
	startQueryAPI();

    // parse
    const auto&[argc, dpArgv] = inputString();
    auto program = makeArgumentParser(argc, dpArgv);
    try 
    {
        program->parse_args(argc, dpArgv);
    }
    catch (const std::runtime_error& err) 
    {       
        if ((strcmp("help called", err.what()) == 0))
        {
            program->print_help();
        }
        else
        {
            printer(err.what());
            program->print_help();
            assert(0);
            return;
        }
    }	

	endQueryAPI(program, argc, dpArgv);
}


std::tuple<int, char**> QueryAPI::inputString()
{
    std::string programName("queryparse");
    int argc = 5;
    auto dpArgv = makeArgv(argc, programName.c_str(), "--help", "-3", "-3", "-3");

    return { argc, dpArgv };
}

char** QueryAPI::makeArgv(int count, ...)
{
    va_list args;
    int i;
    char **dpArgv = (char **)malloc((count + 1) * sizeof(char*));
    char *temp;
    va_start(args, count);
    for (i = 0; i < count; i++) {
        temp = va_arg(args, char*);
        dpArgv[i] = (char*)malloc(sizeof(temp) + 1);
        strcpy_s(dpArgv[i], strlen(temp) + 1, temp);
    }
    dpArgv[i] = NULL;
    va_end(args);

    return dpArgv;
}


std::shared_ptr<argparse::ArgumentParser> QueryAPI::makeArgumentParser(const int& argc, char **dpArgv)
{
    std::shared_ptr<argparse::ArgumentParser> program = std::make_shared<argparse::ArgumentParser>("queryparse");

    addPositionalArguments(program, argc);
    addOptionalArguments(program, argc);

    return program;
}

void QueryAPI::addPositionalArguments(std::shared_ptr<argparse::ArgumentParser> program, const int& dpArgv)
{
    program->add_argument("input_query")
        .help("input query")
        .action([](const std::string& value)
            {
                return std::stoi(value);
            });
}

void QueryAPI::addOptionalArguments(std::shared_ptr<argparse::ArgumentParser> program, const int& argc)
{
    // 1.
    {
        // use std::stoi
        program->add_argument("--square")
            .help("display the square of a given integer")
            .default_value(false)
            .implicit_value(true);
        program->add_argument("-s", "--square");
    }

    // 2.
    {
        // use std::stoi
        program->add_argument("--integer")
            .help("Input number")
            .default_value(false)
            .implicit_value(true);
        program->add_argument("-i", "--square");
    }

    // 3.
    {
        // use std::stof
        program->add_argument("--floats")
            .help("Vector of floats")
            .default_value(false)
            .implicit_value(true)
            .nargs(argc);
        program->add_argument("-f", "--square");
    }

    // 4.
    {
        // use std::stod
        program->add_argument("--query_point")
            .help("3D query point")
            .default_value(false)
            .implicit_value(true)
            .nargs(3);
        program->add_argument("-q", "--square");
    }
}


void QueryAPI::startQueryAPI()
{
	printer("Start Query Parse API");
}

void QueryAPI::endQueryAPI(std::shared_ptr<argparse::ArgumentParser> program, const int& argc, char **dpArgv)
{
    for (int i = argc - 1; i >= 1; i--)
        free(dpArgv[i]);
    free(dpArgv);

    printOutput(program);
}

void QueryAPI::printOutput(std::shared_ptr<argparse::ArgumentParser> program)
{
    try
    {
        if ((*program)["--square"] == true)
        {
            auto input = program->get<int>("input_query");
            printer(std::to_wstring(input * input));
        }
        else if ((*program)["--integer"] == true)
        {

        }
        else if ((*program)["--floats"] == true)
        {

        }
        else if ((*program)["--query_point"] == true)
        {

        }
        else
        {
            // maybe --help
        }
    }
    catch (const std::exception& err)
    {
        printer(err.what());
    }
}


void QueryAPI::printer(std::wstring str)
{
    std::cout << str.c_str() << std::endl;
}

void QueryAPI::printer(const char* str)
{
    size_t cn;
    auto len = static_cast<int>(strlen(str));
    std::wstring wstr(L' ', len + 1);
    mbstowcs_s(&cn, &wstr[0], len + 1, str, len + 1);

    printer(wstr);
}
