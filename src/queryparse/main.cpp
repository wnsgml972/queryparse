#include "define.h"
#include "QueryAPI.h"

// main app start
int main()
{
    queryparse::QueryAPI::GetInstance()->runQueryAPI();

    system("pause");

	return 0;
}