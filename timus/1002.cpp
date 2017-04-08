#include <cstdint>
#include <string>
#include <fstream>
#include <vector>
#include <list>

#include "1002.h"

namespace n1002
{

struct WordNumber
{
    std::string m_word;
    std::string m_number;
    bool operator< (const WordNumber& wn)
    {
        return m_number < wn.m_number;
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
    std::string c(1);
    c[0] = number[position];
    auto it = std::lower_bound(wordNumbers.begin(), wordNumbers.end(), c);
    if (wordNumbers.end() == it)
    {
        return false;
    }
    while (*it[0] == c[0])
    {
        if (number.compare(position, it->size(), *it))
        {
            std::list<std::vector<WordNumber>::const_iterator> tmpResult;
            if (getWords(tmpResult, number, position + it->size(), wordNumbers))
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
    size_t wordsCount;
    in >> wordsCount;
    std::vector<WordNumber> wordNumbers(wordsCount);
    for (size_t i = 0; i < wordsCount; ++i)
    {
        in >> wordNumbers[i].m_word;
        std::transform(
            wordNumbers[i].m_word.begin(), wordNumbers[i].m_word.end(),
            wordNumbers[i].m_number[i].begin(), mapping);
    }
    std::sort(wordNumbers.begin(), wordNumbers.end());




}

} // namespace n1002