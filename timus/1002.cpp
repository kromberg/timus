#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <unordered_set>

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
    std::unordered_set<const WordNumber*>& numbersUsed,
    const std::string& number,
    size_t position,
    const std::vector<WordNumber>& wordNumbers)
{
    std::cout << "Number: " << number << "; position: " << position << '\n';
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
    std::cout << "Lower bound: " << it->m_number << "; c[0] = " << c[0] << '\n';
    while (wordNumbers.end() != it && it->m_number[0] == c[0])
    {
        auto numberIt = numbersUsed.find(&(*it));
        if (numbersUsed.end() != numberIt)
        {
            ++ it;
            continue;
        }
        if (!number.compare(position, it->m_number.size(), it->m_number))
        {
            std::list<std::vector<WordNumber>::const_iterator> tmpResult;
            numbersUsed.insert(&(*it));
            if (getWords(tmpResult, numbersUsed, number, position + it->m_number.size(), wordNumbers))
            {
                tmpResult.push_front(it);
                std::cout << "Adding " << it->m_word << '\n';
                if (result.empty() || tmpResult.size() < result.size())
                {
                    result = std::move(tmpResult);
                }
            }
            numbersUsed.erase(&(*it));
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
        size_t wordsCount;
        in >> wordsCount;
        std::vector<WordNumber> wordNumbers(wordsCount);
        for (size_t i = 0; i < wordsCount; ++i)
        {
            in >> wordNumbers[i].m_word;
            std::transform(
                wordNumbers[i].m_word.begin(), wordNumbers[i].m_word.end(),
                std::back_inserter(wordNumbers[i].m_number), mapping);
            //std::cout << wordNumbers[i].m_word << " -> " << wordNumbers[i].m_number << '\n';
        }
        std::sort(wordNumbers.begin(), wordNumbers.end());

        std::list<std::vector<WordNumber>::const_iterator> res;
        std::unordered_set<const WordNumber*> numbersUsed;

        if (getWords(res, numbersUsed, number, 0, wordNumbers))
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