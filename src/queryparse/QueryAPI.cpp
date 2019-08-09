
#include "QueryAPI.h"
#include "argparse.hpp"
#include "ConsolePrinter.h"
#include "ConsoleInputter.h"

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
    const auto&[argc, dpArgv] = m_inputter->makeArgcArgv(L"queryparse");

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
            return;
        }
    }

	endQueryAPI(program, argc, dpArgv);
}

void queryparse::QueryAPI::Initialize()
{
    OnInitialize();

    m_inputter = std::make_shared<queryparse::ConsoleInputter>();
    m_printer = std::make_shared<queryparse::ConsolePrinter>();
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
        .help("[Data] [Tabel]")
        .nargs(2)
        .action([](const std::string& value)
            {
                return StringConverter::string2wstring(value);
            });

    program->add_argument("input_query")
        .help("[Data] [Tabel] [?]")
        .nargs(3)
        .action([](const std::string& value)
            {
                return StringConverter::string2wstring(value);
            });

    program->add_argument("input_query")
        .help("[Data] [Tabel]  [?]  [?]")
        .nargs(3)
        .action([](const std::string& value)
            {
                return StringConverter::string2wstring(value);
            });
}

void queryparse::QueryAPI::addOptionalArguments(std::shared_ptr<argparse::ArgumentParser> program, const int& argc)
{
    {
        program->add_argument("-c", "--create")
            .help("Create Data")
            .default_value(false)
            .implicit_value(true);
    }

    {
        program->add_argument("-r", "--read")
            .help("Read Data")
            .default_value(false)
            .implicit_value(true)
            .nargs(argc);
    }

    {
        program->add_argument("-u", "--update")
            .help("Update Data")
            .default_value(false)
            .implicit_value(true);
    }

    {
        program->add_argument("-d", "--delete")
            .help("Delete Data")
            .default_value(false)
            .implicit_value(true);
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
        // Get Spilted Query
        auto spiltedQuery = program->get<std::vector<std::wstring>>("input_query");

        // Check Option (enable -sifq Option All)
        auto createOption = program->get<bool>("--create");
        auto readOption = program->get<bool>("--read");
        auto updateOption = program->get<bool>("--update");
        auto deleteOption = program->get<bool>("--delete");

        if (createOption)
        {
            int a = 3;
        }
        if (readOption)
        {
            int a = 3;
        }
        if (updateOption)
        {
            int a = 3;
        }
        if (deleteOption)
        {
            int a = 3;
        }
    }
    catch (const std::exception& err)
    {
        m_printer->print(err.what());
    }
}
