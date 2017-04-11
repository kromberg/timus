#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <unordered_set>
#include <algorithm>

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

    int8_t m_used = false;

    bool operator< (const WordNumber& wn) const
    {
        uint8_t i1 = 0, i2 = 0, size1 = m_word.size(), size2 = wn.m_word.size();
        for (; i1 < size1 && i2 < size2; ++i1, ++i2)
        {
            char c1 = mapping(m_word[i1]);
            char c2 = mapping(wn.m_word[i2]);
            if (c1 < c2)
            {
                return true;
            }
            else if (c1 > c2)
            {
                return false;
            }
        }
        return size1 < size2;
    }

    bool operator< (const std::string& number) const
    {
        uint8_t i1 = 0, i2 = 0, size1 = m_word.size(), size2 = number.size();
        for (; i1 < size1 && i2 < size2; ++i1, ++i2)
        {
            char c1 = mapping(m_word[i1]);
            char c2 = number[i2];
            if (c1 < c2)
            {
                return true;
            }
            else if (c1 > c2)
            {
                return false;
            }
        }
        return size1 < size2;
    }
};

static bool compare(const std::string& number, const size_t pos, const std::string& word)
{
    const uint8_t numberSize = number.size();
    const uint8_t wordSize = word.size();
    uint8_t numberI = pos, wordI = 0;
    for (; numberI < numberSize && wordI < wordSize; ++numberI, ++wordI)
    {
        if (number[numberI] != mapping(word[wordI]))
        {
            return false;
        }
    }
    return wordI == wordSize;
}

bool getWords(
    std::list<uint16_t>& result,
    const std::string& number,
    uint8_t position,
    std::vector<WordNumber>& wordNumbers)
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
    
    while (wordNumbers.end() != it && mapping(it->m_word[0]) == c[0])
    {
        if (it->m_used)
        {
            ++ it;
            continue;
        }
        if (compare(number, position, it->m_word))
        {
            std::list<uint16_t> tmpResult;
            it->m_used = true;
            if (getWords(tmpResult, number, position + it->m_word.size(), wordNumbers))
            {
                tmpResult.push_front(std::distance(wordNumbers.begin(), it));
                
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
            /*wordNumbers[i].m_number.reserve(wordNumbers[i].m_word.size() + 1);
            std::transform(
                wordNumbers[i].m_word.begin(), wordNumbers[i].m_word.end(),
                std::back_inserter(wordNumbers[i].m_number), mapping);*/
            //
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


int32_t main(int32_t argc, char* argv[])
{
    std::ifstream fin("in.txt");
    std::ofstream fout("out.txt");

    n1002::solve(fin, fout);

    return 0;
}