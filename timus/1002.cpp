#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <array>
#include <memory>

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
};

struct NumberCount
{
    std::array<std::unique_ptr<NumberCount>, 10> m_numbers;
    std::list<uint16_t> m_indices;

    void setNumber(const char* word, const size_t size, const uint16_t index)
    {
        if (0 == size)
        {
            m_indices.push_back(index);
            return ;
        }
        uint16_t idx = static_cast<uint16_t>(mapping(*word) - '0');
        if (!m_numbers[idx])
        {
            m_numbers[idx].reset(new NumberCount);
        }
        m_numbers[idx]->setNumber(word + 1, size - 1, index);
    }

    void getNumbers(
        std::list<NumberCount*>& res,
        const char* number,
        const size_t size)
    {
        if (!m_indices.empty())
        {
            res.push_front(this);
        }

        if (0 == size)
        {
            return ;
        }

        uint16_t idx = static_cast<uint16_t>(*number - '0');
        if (!m_numbers[idx])
        {
            return ;
        }

        m_numbers[idx]->getNumbers(res, number + 1, size - 1);
    }

    void print(std::ostream& out, const std::string& spaces=std::string(""))
    {
        if (!m_indices.empty())
        {
            out << spaces << "indices : ";
            for (auto idx : m_indices)
            {
                out << idx << " ";
            }
            out << '\n';
        }
        for (size_t i = 0; i < 10; ++i)
        {
            if (m_numbers[i])
            {
                out << spaces << "[" << i << "] : ";
                out << '\n';
                out << spaces << "{\n";
                m_numbers[i]->print(out, spaces + std::string(" "));
                out << spaces << "}\n";
            }
        }
    }
};

bool getNumbers(
    std::list<uint16_t>& numbers,
    const char* number,
    const size_t size,
    NumberCount& numberCount,
    std::vector<std::string>& words,
    int16_t resultSize = 0)
{
    if (0 == size)
    {
        return true;
    }

    std::cout << "Number: " << number << "; size: " << size << '\n';

    std::list<NumberCount*> currNumbers;

    numberCount.getNumbers(currNumbers, number, size);

    if (currNumbers.empty())
    {
        return false;
    }

    std::cout << currNumbers.size() << " found\n";

    for (auto currNumber : currNumbers)
    {
        uint16_t currIdx = currNumber->m_indices.front();
        currNumber->m_indices.pop_front();
        std::cout << "Processing " << words[currIdx] << "\n";
        std::list<uint16_t> tmpNumbers;
        
        if (getNumbers(tmpNumbers, number + words[currIdx].size(), size - words[currIdx].size(), numberCount, words,
            (resultSize == 0) ? numbers.size() : resultSize))
        {
            if ((resultSize == 0 || resultSize > tmpNumbers.size() + 1) &&
                (numbers.empty() || tmpNumbers.size() + 1 < numbers.size()))
            {
                tmpNumbers.push_front(currIdx);
                numbers = std::move(tmpNumbers);
            }
            if (1 == numbers.size())
            {
                currNumber->m_indices.push_back(currIdx);
                break;
            }
        }
        currNumber->m_indices.push_back(currIdx);
    }
    if (numbers.empty())
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
        std::vector<std::string> words(wordsCount);
        NumberCount numberCount;
        for (uint16_t i = 0; i < wordsCount; ++i)
        {
            in >> words[i];
            numberCount.setNumber(words[i].c_str(), words[i].size(), i);
        }
        numberCount.print(std::cout);

        std::list<uint16_t> numbers;
        if (getNumbers(numbers, number.c_str(), number.size(), numberCount, words))
        {
            for (auto idx : numbers)
            {
                out << words[idx] << ' ';
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