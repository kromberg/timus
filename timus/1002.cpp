#include <cstdint>
#include <string>
#include <fstream>
#include <vector>

#include "1002.h"

using namespace std;

namespace n1002
{

char mapping(char c)
{
    static char charToNumber[] =
    {
        '2', '2', '2',
        '3', '3', '3',
        '4', '4',
        '1', '1',
        '5', '5',
        '6', '6',
        '0',
        '7',
        '0',
        '7', '7',
        '8', '8', '8',
        '9', '9', '9',
        '0'
    };
    return charToNumber[c - 'a'];
}

void solve(istream& in, ostream& out)
{
    string number;
    in >> number;
    size_t wordsCount;
    in >> wordsCount;
    vector<string> numbers(wordsCount);
    for (size_t i = 0; i < wordsCount; ++i)
    { }
    
}

} // namespace n1002