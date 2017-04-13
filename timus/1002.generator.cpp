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
    if (argc < 5)
    {
        std::cerr << "invalid number of arguments\n";
        return 1;
    }
    std::string filename(argv[1]);
    const uint32_t size = std::stoul(argv[2]);
    if (size > 100)
    {
        std::cerr << "size > 100\n";
        return 2;
    }
    uint32_t wordsCount = std::stoul(argv[3]);
    if (wordsCount > 50000)
    {
        std::cerr << "wordsCount > 100\n";
        return 2;
    }
    uint32_t maxModulo = std::stoul(argv[4]);
    if (maxModulo > size)
    {
        std::cerr << "maxModulo > size\n";
        return 2;
    }

    std::string word;
    word.resize(size);
    for (auto& c : word)
    {
        c = rand() % ('z' - 'a') + 'a';
    }
    std::string number;
    number.resize(size);
    std::transform(word.begin(), word.end(), number.begin(), mapping);

    std::ofstream fout(filename.c_str());
    fout << number << '\n';
    
    fout << wordsCount << '\n';

    for (auto c : word)
    {
        fout << c << '\n';
        if (!-- wordsCount)
        {
            return 0;
        }
    }

    for (size_t modulo = 2; modulo < maxModulo; ++modulo)
    {
        size_t i = 0;
        for (auto c : word)
        {
            fout << c;
            if (++i % modulo == 0)
            {
                fout << '\n';
                if (!-- wordsCount)
                {
                    return 0;
                }
            }
        }
        if (i % modulo != 0)
        {
            fout << '\n';
            if (!-- wordsCount)
            {
                return 0;
            }
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