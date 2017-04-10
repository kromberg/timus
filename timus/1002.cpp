#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>

#include "1002.h"

namespace n1002
{

struct WordNumber
{
    std::string m_word;
    std::string m_number;
    bool operator< (const WordNumber& wn) const
    {
        return m_number < wn.m_number;
    }

    bool operator< (const std::string& number) const
    {
        return m_number < number;
    }
};

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

bool getWords(
    std::list<std::vector<WordNumber>::const_iterator>& result,
    const std::string& number,
    size_t position,
    const std::vector<WordNumber>& wordNumbers)
{
    if (number.size() == position)
    {
        return true;
    }
    std::string c(1, number[position]);
    auto it = std::lower_bound(wordNumbers.begin(), wordNumbers.end(), c);
    if (wordNumbers.end() == it)
    {
        return false;
    }
    while (it->m_number[0] == c[0])
    {
        if (number.compare(position, it->m_number.size(), it->m_number))
        {
            std::list<std::vector<WordNumber>::const_iterator> tmpResult;
            if (getWords(tmpResult, number, position + it->m_number.size(), wordNumbers))
            {
                tmpResult.push_front(it);
                if (result.empty() || tmpResult.size() < result.size())
                {
                    result = std::move(tmpResult);
                }
            }
        }

        ++ it;
    }

    if (result.empty())
    {
        return false;
    }

    return true;
}

void solve(std::istream& in, std::ostream& out)
{
    std::string number;
    in >> number;
    while (number != "-1")
    {
        size_t wordsCount;
        in >> wordsCount;
        std::vector<WordNumber> wordNumbers(wordsCount);
        for (size_t i = 0; i < wordsCount; ++i)
        {
            in >> wordNumbers[i].m_word;
            std::transform(
                wordNumbers[i].m_word.begin(), wordNumbers[i].m_word.end(),
                std::back_inserter(wordNumbers[i].m_number), mapping);
            std::cout << wordNumbers[i].m_word << " -> " << wordNumbers[i].m_number << '\n';
        }
        std::sort(wordNumbers.begin(), wordNumbers.end());

        std::list<std::vector<WordNumber>::const_iterator> res;

        if (getWords(res, number, 0, wordNumbers))
        {
            for (const auto& it : res)
            {
                out << it->m_word << ' ';
            }
            out << '\n';
        }
        else
        {
            out << "No solution.\n";
        }
        in >> number;
    }
}

} // namespace n1002