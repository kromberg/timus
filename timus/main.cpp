#include <cstdint>
#include "1002.h"

int32_t main(int32_t argc, char* argv[])
{
    std::ifstream fin("in.txt");
    std::ofstream fout("out.txt");

    n1002::solve(fin, fout);

    return 0;
}

