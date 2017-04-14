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

#define LOG(ARGS...) \
    std::cout << ARGS;

namespace n1002
{

static uint16_t mapping(char c)
{
    static uint16_t charToNumber[26] =
    {
        2, 2, 2, 3, 3, 3, 4, 4, 1, 1, 5, 5, 6, 6, 0, 7, 0, 7, 7, 8, 8, 8, 9, 9, 9, 0
    };
    return charToNumber[c - 'a'];
}

struct NumberCount
{
    std::unique_ptr<NumberCount> m_numbers[10];
    std::list<uint16_t> m_indices;

    void setNumber(const char* word, const size_t size, const uint16_t index)
    {
        if (0 == size)
        {
            m_indices.push_back(index);
            return ;
        }
        uint16_t idx = mapping(*word);
        if (!m_numbers[idx])
        {
            m_numbers[idx].reset(new NumberCount);
        }
        m_numbers[idx]->setNumber(word + 1, size - 1, index);
    }

    bool getNumber(uint16_t& numberIdx, const char* number, const size_t size)
    {
        if (0 == size)
        {
            if (!m_indices.empty())
            {
                numberIdx = m_indices.front();
                return true;
            }
            return false;
        }

        uint16_t idx = static_cast<uint16_t>((*number) - '0');
        if (!m_numbers[idx])
        {
            return false;
        }

        return m_numbers[idx]->getNumber(numberIdx, number + 1, size - 1);
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

struct Item
{
    uint16_t m_size;
    uint16_t m_prevSize;
    uint16_t m_idx;
    Item(const size_t size):
        m_size(size + 1),
        m_prevSize(0),
        m_idx(0)
    {}
};

void getNumbers(
    std::list<uint16_t>& numbers,
    const char* number,
    const size_t size,
    NumberCount& numberCount)
{
    std::vector<Item> sizeToNumbers(size + 1, Item(size));

    uint16_t numberIdx;
    if (numberCount.getNumber(numberIdx, number, 1))
    {
        sizeToNumbers[1].m_size = 1;
        sizeToNumbers[1].m_idx = numberIdx;
    }

    LOG('[' << 1 << "] = <" << sizeToNumbers[1].m_size << "; " << sizeToNumbers[1].m_idx << ">\n");

    for (size_t currSize = 2; currSize <= size; ++currSize)
    {
        if (numberCount.getNumber(numberIdx, number, currSize))
        {
            sizeToNumbers[currSize].m_size = 1;
            sizeToNumbers[currSize].m_idx = numberIdx;
        }
        for (size_t prevSize = 1; prevSize < currSize; ++prevSize)
        {
            if (sizeToNumbers[prevSize].m_size == size + 1) 
            {
                continue;
            }
            if (sizeToNumbers[prevSize].m_size + 1 >= sizeToNumbers[currSize].m_size)
            {
                continue;
            }
            if (!numberCount.getNumber(numberIdx, number + prevSize, currSize - prevSize))
            {
                continue;
            }
            sizeToNumbers[currSize].m_size = sizeToNumbers[prevSize].m_size + 1;
            sizeToNumbers[currSize].m_prevSize = prevSize;
            sizeToNumbers[currSize].m_idx = numberIdx;
        }
        LOG('[' << currSize << "] = <" << sizeToNumbers[currSize].m_size << "; " << sizeToNumbers[currSize].m_idx << ">\n");
    }

    if (sizeToNumbers[size].m_size == size + 1)
    {
        return ;
    }
    size_t currSize = size;
    while (currSize != 0)
    {
        numbers.push_front(sizeToNumbers[currSize].m_idx);
        currSize = sizeToNumbers[currSize].m_prevSize;
    }
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

        std::list<uint16_t> numbers;
        getNumbers(numbers, number.c_str(), number.size(), numberCount);
        if (!numbers.empty())
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