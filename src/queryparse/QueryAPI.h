#pragma once

#include "define.h"

namespace argparse
{
    class ArgumentParser;
}

namespace queryparse
{
    class BaseInputter;
    class BasePrinter;

    // thread safe singleton
    class QueryAPI
    {
    public:
        QueryAPI() = default;
        virtual ~QueryAPI() = default;

        // run API
        void runQueryAPI();

    protected:
        virtual void OnInitialize() = 0;
        virtual void addCustomOptionalArguments(std::shared_ptr<argparse::ArgumentParser> program) { /* Implement in subclass */ }
        virtual void addCustomPrintOutput(std::shared_ptr<argparse::ArgumentParser> program) { /* Implement in subclass */ }

        void setInputter(std::shared_ptr<BaseInputter> inputter);
        void setPrinter(std::shared_ptr<BasePrinter> printer);

    private:
        // main
        void queryAPI();
        void Initialize();

        // make arg parser
        std::shared_ptr<argparse::ArgumentParser> makeArgumentParser(const int& argc, char **dpArgv);
        void addDefaultPositionalArguments(std::shared_ptr<argparse::ArgumentParser> program, const int& argc);
        void addDefaultOptionalArguments(std::shared_ptr<argparse::ArgumentParser> program);

        // start end queryAPI callback
        void startQueryAPI();
        void endQueryAPI(std::shared_ptr<argparse::ArgumentParser> program, const int& argc, char **dpArgv);
        void printOutput(std::shared_ptr<argparse::ArgumentParser> program);

    private:
        std::thread m_runnerThread;
        std::shared_ptr<BaseInputter> m_inputter;
        std::shared_ptr<BasePrinter> m_printer;
        bool m_isSetInputter;
        bool m_isSetPrinter;
    };
}
