#include "1002.h"

#include <list>
#include <string>

static char aLettersNumbersMap[int32_t('z')] = { 0 };

void _FormLettersNumbersMap()
{
    aLettersNumbersMap['i'] = '1';
    aLettersNumbersMap['j'] = '1';
    aLettersNumbersMap['a'] = '2';
    aLettersNumbersMap['b'] = '2';
    aLettersNumbersMap['c'] = '2';
    aLettersNumbersMap['d'] = '3';
    aLettersNumbersMap['e'] = '3';
    aLettersNumbersMap['f'] = '3';
    aLettersNumbersMap['g'] = '4';
    aLettersNumbersMap['h'] = '4';
    aLettersNumbersMap['k'] = '5';
    aLettersNumbersMap['l'] = '5';
    aLettersNumbersMap['m'] = '6';
    aLettersNumbersMap['n'] = '6';
    aLettersNumbersMap['p'] = '7';
    aLettersNumbersMap['r'] = '7';
    aLettersNumbersMap['s'] = '7';
    aLettersNumbersMap['t'] = '8';
    aLettersNumbersMap['u'] = '8';
    aLettersNumbersMap['v'] = '8';
    aLettersNumbersMap['w'] = '9';
    aLettersNumbersMap['x'] = '9';
    aLettersNumbersMap['y'] = '9';
    aLettersNumbersMap['o'] = '0';
    aLettersNumbersMap['q'] = '0';
    aLettersNumbersMap['z'] = '0';
}

template <typename T>
inline T min(T& t1, T& t2)
{
    return (t1 > t2) : t2 ? t1;
}

struct Number
{
    bool m_bUsed;
    int32_t m_i32NumberSize;
    char* m_szNumber;
};

void _FormNumber(const char* szWord, Number &number)
{
    number.m_i32NumberSize = strlen(szWord);
    number.m_szNumber = new char[number.m_i32NumberSize + 1];
    char *sTmpNumber = number.m_szNumber;
    while (*szWord++)
    {
        *sTmpNumber++ = aLettersNumbersMap[*szWord];
    }
    *sTmpNumber = '\0';
}

bool _RecursiveGetSolution(
    char* szTelephoneNumber,
    int32_t i32TelephoneNumberSize,
    int32_t i32NumbersCount,
    Number* pNumbers,
    std::list<Number> &lNumbers)
{
    std::list<Number> lMinNumbers;
    for (int32_t i = 0; i < i32NumbersCount; ++i)
    {
        std::list<Number> lTmpNumbers;
        if (!pNumbers[i].m_bUsed &&
            (i32TelephoneNumberSize >= pNumbers[i].m_i32NumberSize) &&
            !strncmp(szTelephoneNumber, pNumbers[i].m_szNumber, pNumbers[i].m_i32NumberSize))
        {
            pNumbers[i].m_bUsed = true;
            bool result = _RecursiveGetSolution(
                szTelephoneNumber + pNumbers[i].m_i32NumberSize,
                i32TelephoneNumberSize - pNumbers[i].m_i32NumberSize,
                i32NumbersCount,
                pNumbers,
                lTmpNumbers);

            if (result)
            {
                if (lMinNumbers.empty() || lMinNumbers.size() > lTmpNumbers.size())
                {
                    lMinNumbers = lTmpNumbers;
                }
            }
            pNumbers[i].m_bUsed = false;
        }
    }
    return lMinNumbers.empty() ? false : true;
}

std::list<Number> _GetSolution(char* szTelephoneNumber, int32_t i32NumbersCount, Number* pNumbers)
{
    static Number noSolution = { false, 12, "No solution." };

    int32_t i32TelephoneNumberSize = strlen(szTelephoneNumber);

    std::list<Number> lMinNumbers;
    for (int32_t i = 0; i < i32NumbersCount; ++i)
    {
        std::list<Number> lTmpNumbers;
        if ((i32TelephoneNumberSize >= pNumbers[i].m_i32NumberSize) &&
            !strncmp(szTelephoneNumber, pNumbers[i].m_szNumber, pNumbers[i].m_i32NumberSize))
        {
            pNumbers[i].m_bUsed = true;
            bool result = _RecursiveGetSolution(
                szTelephoneNumber + pNumbers[i].m_i32NumberSize,
                i32TelephoneNumberSize - pNumbers[i].m_i32NumberSize,
                i32NumbersCount,
                pNumbers,
                lTmpNumbers);

            if (result)
            {
                if (lMinNumbers.empty() || lMinNumbers.size() > lTmpNumbers.size())
                {
                    lMinNumbers = lTmpNumbers;
                }
            }
            pNumbers[i].m_bUsed = false;
        }
    }
    if (lMinNumbers.empty())
    {
        lMinNumbers.push_back(noSolution);
    }
    return lMinNumbers;
}

int32_t Solve(FILE *in, FILE *out)
{
    _FormLettersNumbersMap();

    char szTelephoneNumber[101] = { 0 };
    fscanf_s(in, "%s", &szTelephoneNumber);

    while (strncmp(szTelephoneNumber, "-1", sizeof(szTelephoneNumber)))
    {
        int32_t i32WordsCount = 0;
        fscanf_s(in, "%d", &i32WordsCount);

        char word[51];
        Number* pNumbers = new Number[i32WordsCount];

        for (int32_t i = 0; i < i32WordsCount; ++i)
        {
            fscanf_s(in, "%s", &word);
            _FormNumber(word, pNumbers[i]);
            pNumbers[i].m_bUsed = false;
        }

        // TODO: solve


        for (int32_t i = 0; i < i32WordsCount; ++i)
        {
            delete[] pNumbers[i].m_szNumber;
        }
        delete[] pNumbers;

        // get telephone number
        fscanf_s(in, "%s", &szTelephoneNumber);
    }

    return -1;
}
