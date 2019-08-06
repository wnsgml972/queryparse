
#include "QueryAPI.h"
#include "argparse.hpp"
#include "Printer.h"
#include <stdarg.h>

// static initialize
std::unique_ptr<queryparse::QueryAPI> queryparse::QueryAPI::m_instance = {};
std::once_flag queryparse::QueryAPI::m_onceFlag = {};


queryparse::QueryAPI* queryparse::QueryAPI::GetInstance()
{
    std::call_once(queryparse::QueryAPI::m_onceFlag, [&]() {
            m_instance.reset(new queryparse::QueryAPI());
        });


    return m_instance.get();
}

void queryparse::QueryAPI::runQueryAPI()
{
    using namespace std::literals;
    Initialize();

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
void queryparse::QueryAPI::queryAPI()
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
            m_printer->print(err.what());
            program->print_help();
            assert(0);
            return;
        }
    }	

	endQueryAPI(program, argc, dpArgv);
}


void queryparse::QueryAPI::Initialize()
{
    OnInitialize();

    m_printer = std::make_shared<queryparse::Printer>();
}

std::tuple<int, char**> queryparse::QueryAPI::inputString()
{
    std::wstring programName(L"queryparse");
    
    std::wstring text;
    std::wcin >> text;

    int argc = 5;
    auto dpArgv = makeArgv(argc, programName.c_str(), "--help", "-3", "-3", "-3");

    return { argc, dpArgv };
}

char** queryparse::QueryAPI::makeArgv(int count, ...)
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


std::shared_ptr<argparse::ArgumentParser> queryparse::QueryAPI::makeArgumentParser(const int& argc, char **dpArgv)
{
    std::shared_ptr<argparse::ArgumentParser> program = std::make_shared<argparse::ArgumentParser>("queryparse");

    addPositionalArguments(program, argc);
    addOptionalArguments(program, argc);

    return program;
}

void queryparse::QueryAPI::addPositionalArguments(std::shared_ptr<argparse::ArgumentParser> program, const int& dpArgv)
{
    program->add_argument("input_query")
        .help("input query")
        .action([](const std::string& value)
            {
                return std::stoi(value);
            });
}

void queryparse::QueryAPI::addOptionalArguments(std::shared_ptr<argparse::ArgumentParser> program, const int& argc)
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


void queryparse::QueryAPI::startQueryAPI()
{
    m_printer->print("\nStart Query Parse API");
}

void queryparse::QueryAPI::endQueryAPI(std::shared_ptr<argparse::ArgumentParser> program, const int& argc, char **dpArgv)
{
    for (int i = argc - 1; i >= 1; i--)
        free(dpArgv[i]);
    free(dpArgv);

    printOutput(program);
}

void queryparse::QueryAPI::printOutput(std::shared_ptr<argparse::ArgumentParser> program)
{
    try
    {
        if ((*program)["--square"] == true)
        {
            auto input = program->get<int>("input_query");
            m_printer->print(std::to_wstring(input * input));
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
        m_printer->print(err.what());
    }
}
