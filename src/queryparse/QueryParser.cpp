#include "QueryParser.h"
#include "ConsoleInputter.h"
#include "ConsolePrinter.h"

void queryparse::QueryParser::OnInitialize()
{
    setInputter(std::make_shared<ConsoleInputter>());
    setPrinter(std::make_shared<ConsolePrinter>());
}

void queryparse::QueryParser::addCustomOptionalArguments(std::shared_ptr<argparse::ArgumentParser> program)
{

}

void queryparse::QueryParser::addCustomPrintOutput(std::shared_ptr<argparse::ArgumentParser> program)
{

}

