#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>

static char mapping(char c)
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
int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "invalid number of arguments\n";
        return 1;
    }
    std::string filename(argv[1]);

    std::string word;
    word.resize(100);
    for (auto& c : word)
    {
        c = rand() % ('z' - 'a') + 'a';
    }
    std::string number;
    number.resize(100);
    std::transform(word.begin(), word.end(), number.begin(), mapping);

    std::ofstream fout(filename.c_str());
    fout << number << '\n';
    uint16_t wordsCount = 50000;
    fout << wordsCount << '\n';

    for (auto c : word)
    {
        fout << c << '\n';
        -- wordsCount;
    }

    for (size_t modulo = 2; modulo < 15; ++modulo)
    {
        size_t i = 0;
        for (auto c : word)
        {
            fout << c;
            if (++i % modulo == 0)
            {
                fout << '\n';
                -- wordsCount;
            }
        }
        if (i % modulo != 0)
        {
            fout << '\n';
            -- wordsCount;
        }
    }

    for (size_t i = 0; i < wordsCount; ++i)
    {
        std::string s;
        std::generate_n(std::back_inserter(s), rand() % 15 + 1, [] () -> char {
            return rand() % ('z' - 'a') + 'a';
        });
        fout << s << '\n';
    }
    fout << "-1\n";
    fout.close();
    
    return 0;
}