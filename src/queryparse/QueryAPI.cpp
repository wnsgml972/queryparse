#include "QueryAPI.h"
#include "argparse.hpp"
#include "BaseInputter.h"
#include "BasePrinter.h"

void queryparse::QueryAPI::runQueryAPI()
{
    using namespace std::literals;

    Initialize();

    if (!m_isSetPrinter || !m_isSetInputter)
    {
        // Set Inpuuter And Printer
        assert(0);
        return;
    }

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
    m_isSetInputter = false;
    m_isSetPrinter = false;

    OnInitialize();
}

void queryparse::QueryAPI::setInputter(std::shared_ptr<BaseInputter> inputter)
{
    m_inputter = inputter;
    if (m_inputter)
        m_isSetInputter = true;
}

void queryparse::QueryAPI::setPrinter(std::shared_ptr<BasePrinter> printer)
{
    m_printer = printer;
    if (m_printer)
        m_isSetPrinter = true;
}

std::shared_ptr<argparse::ArgumentParser> queryparse::QueryAPI::makeArgumentParser(const int& argc, char **dpArgv)
{
    std::shared_ptr<argparse::ArgumentParser> program = std::make_shared<argparse::ArgumentParser>("queryparse");

    addDefaultPositionalArguments(program, argc);
    addDefaultOptionalArguments(program);

    return program;
}

void queryparse::QueryAPI::addDefaultPositionalArguments(std::shared_ptr<argparse::ArgumentParser> program, const int& argc)
{
    int queryCountExceptProgramNameAndOption = argc - 2;

    program->add_argument("input_query")
        .help("[Data] [Tabel]")
        .nargs(queryCountExceptProgramNameAndOption)
        .action([](const std::string& value)
            {
                return StringConverter::string2wstring(value);
            });
}

void queryparse::QueryAPI::addDefaultOptionalArguments(std::shared_ptr<argparse::ArgumentParser> program)
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
            .implicit_value(true);
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

    addCustomOptionalArguments(program);
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
            // INSERT INTO 테이블명 (열1, 열2) VALUES (값1, 값2);

            // insert into [tabel] values [tabel-key, tabel-key, tabel-key]
            int a = 3;
        }
        if (readOption)
        {
            // SELECT 열이름 FROM 테이블명;

            // select [*] from [tabel]
            int a = 3;
        }
        if (updateOption)
        {
            // DELETE FROM 테이블명 WHERE 조건;
            int a = 3;
        }
        if (deleteOption)
        {
            // UPDATE 테이블명 SET 열명 = 값, 열명 = 값 WHERE 조건;

            int a = 3;
        }
    }
    catch (const std::exception& err)
    {
        m_printer->print(err.what());
    }

    addCustomPrintOutput(program);
}
