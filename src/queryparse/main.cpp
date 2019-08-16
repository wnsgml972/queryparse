#include "define.h"
#include "QueryParser.h"

// main app start
int main()
{
    std::unique_ptr<queryparse::QueryParser> queryparser = std::make_unique<queryparse::QueryParser>();
    queryparser->runQueryAPI();

    system("pause");

	return 0;
}