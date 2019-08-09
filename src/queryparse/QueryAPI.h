#pragma once

#include "define.h"

namespace argparse
{
    class ArgumentParser;
}

namespace queryparse
{
    class ConsoleInputter;
    class ConsolePrinter;

    // thread safe singleton
    class QueryAPI
    {
    public:
        // instance
        static QueryAPI* GetInstance();

        // run API
        void runQueryAPI();

    protected:
        virtual void OnInitialize() { /* Implement in subclass */ }
        virtual void printOutput(std::shared_ptr<argparse::ArgumentParser> program);

    private:
        // main
        void queryAPI();
        void Initialize();

        // make arg parser
        std::shared_ptr<argparse::ArgumentParser> makeArgumentParser(const int& argc, char **dpArgv);
        void addPositionalArguments(std::shared_ptr<argparse::ArgumentParser> program, const int& argc);
        void addOptionalArguments(std::shared_ptr<argparse::ArgumentParser> program, const int& argc);

        // start end queryAPI callback
        void startQueryAPI();
        void endQueryAPI(std::shared_ptr<argparse::ArgumentParser> program, const int& argc, char **dpArgv);

    private:
        std::thread m_runnerThread;
        std::shared_ptr<ConsoleInputter> m_inputter;
        std::shared_ptr<ConsolePrinter> m_printer;

        //////////////////////////////////////////////////////////////////////////
        static std::unique_ptr<QueryAPI> m_instance;
        static std::once_flag m_onceFlag;

        QueryAPI() = default;
        QueryAPI(const QueryAPI &) = delete;
        QueryAPI &operator=(const QueryAPI &) = delete;
    };
}
