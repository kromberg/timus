#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <unordered_set>
#include <algorithm>

#include "1002.h"

namespace n1002
{

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

struct WordNumber
{
    std::string m_word;
    std::string m_number;

    int8_t m_used = false;

    bool operator< (const WordNumber& wn) const
    {
        return m_number < wn.m_number;
    }

    bool operator< (const std::string& number) const
    {
        return m_number < number;
    }
};

static bool compare(const std::string& number, const size_t pos, const std::string& number2)
{
    return !number.compare(pos, number2.size(), number2);
}

bool getWords(
    std::list<uint16_t>& result,
    const std::string& number,
    uint8_t position,
    std::vector<WordNumber>& wordNumbers)
{
    std::cout << "Number: " << number << "; position: " << (int32_t)position << '\n';
    if (number.size() == position)
    {
        std::cout << "The end of the number is reached" << '\n';
        return true;
    }
    std::string c(1, number[position]);
    auto it = std::lower_bound(wordNumbers.begin(), wordNumbers.end(), c);
    if (wordNumbers.end() == it)
    {
        std::cout << "Lower bound is not found" << '\n';
        return false;
    }
    std::cout << "Lower bound: " << it->m_word << "; c[0] = " << c[0] << '\n';
    while (wordNumbers.end() != it && it->m_number[0] == c[0])
    {
        if (it->m_used)
        {
            ++ it;
            continue;
        }
        if (compare(number, position, it->m_number))
        {
            std::list<uint16_t> tmpResult;
            it->m_used = true;
            if (getWords(tmpResult, number, position + it->m_number.size(), wordNumbers))
            {
                tmpResult.push_front(std::distance(wordNumbers.begin(), it));
                std::cout << "Adding " << it->m_word << '\n';
                if (result.empty() || tmpResult.size() < result.size())
                {
                    result = std::move(tmpResult);
                }
            }
            it->m_used = false;
        }

        ++ it;
    }

    if (result.empty())
    {
        std::cout << "Result is empty" << '\n';
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
        uint16_t wordsCount;
        in >> wordsCount;
        std::vector<WordNumber> wordNumbers(wordsCount);
        for (uint16_t i = 0; i < wordsCount; ++i)
        {
            in >> wordNumbers[i].m_word;
            wordNumbers[i].m_number.reserve(wordNumbers[i].m_word.size() + 1);
            std::transform(
                wordNumbers[i].m_word.begin(), wordNumbers[i].m_word.end(),
                std::back_inserter(wordNumbers[i].m_number), mapping);
            //std::cout << wordNumbers[i].m_word << " -> " << wordNumbers[i].m_number << '\n';
        }
        std::sort(wordNumbers.begin(), wordNumbers.end());

        std::list<uint16_t> res;
        if (getWords(res, number, 0, wordNumbers))
        {
            for (const auto idx : res)
            {
                out << wordNumbers[idx].m_word << ' ';
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