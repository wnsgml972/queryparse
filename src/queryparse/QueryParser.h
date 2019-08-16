#pragma once
#include "QueryAPI.h"

namespace queryparse
{
    class QueryParser : public QueryAPI
    {
    public:
        QueryParser() = default;
        virtual ~QueryParser() override = default;

        virtual void OnInitialize() override;
        virtual void addCustomOptionalArguments(std::shared_ptr<argparse::ArgumentParser> program) override;
        virtual void addCustomPrintOutput(std::shared_ptr<argparse::ArgumentParser> program) override;
    };
}