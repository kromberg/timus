#include <stdio.h>
#include <cstdint>
#include "1002.h"

int32_t main(int32_t argc, char* argv[])
{
    FILE* in = fopen("in.txt", "r");
    FILE* out = fopen("out.txt", "w");
    Solve(in, out);
    return 0;
}

