#include "1002.h"

#include <list>
#include <string>

static char aLettersNumbersMap[int32_t('z') - int32_t('a') + 1] = { 0 };

void _FormLettersNumbersMap()
{
    aLettersNumbersMap['i' - 'a'] = '1';
    aLettersNumbersMap['j' - 'a'] = '1';
    aLettersNumbersMap['a' - 'a'] = '2';
    aLettersNumbersMap['b' - 'a'] = '2';
    aLettersNumbersMap['c' - 'a'] = '2';
    aLettersNumbersMap['d' - 'a'] = '3';
    aLettersNumbersMap['e' - 'a'] = '3';
    aLettersNumbersMap['f' - 'a'] = '3';
    aLettersNumbersMap['g' - 'a'] = '4';
    aLettersNumbersMap['h' - 'a'] = '4';
    aLettersNumbersMap['k' - 'a'] = '5';
    aLettersNumbersMap['l' - 'a'] = '5';
    aLettersNumbersMap['m' - 'a'] = '6';
    aLettersNumbersMap['n' - 'a'] = '6';
    aLettersNumbersMap['p' - 'a'] = '7';
    aLettersNumbersMap['r' - 'a'] = '7';
    aLettersNumbersMap['s' - 'a'] = '7';
    aLettersNumbersMap['t' - 'a'] = '8';
    aLettersNumbersMap['u' - 'a'] = '8';
    aLettersNumbersMap['v' - 'a'] = '8';
    aLettersNumbersMap['w' - 'a'] = '9';
    aLettersNumbersMap['x' - 'a'] = '9';
    aLettersNumbersMap['y' - 'a'] = '9';
    aLettersNumbersMap['o' - 'a'] = '0';
    aLettersNumbersMap['q' - 'a'] = '0';
    aLettersNumbersMap['z' - 'a'] = '0';
}

template <typename T>
inline T min(T& t1, T& t2)
{
    return (t1 > t2) : t2 ? t1;
}

struct Number
{
    int32_t m_i32NumberSize;
    char* m_szNumber;
    char* m_szWord;
};

void _FormNumber(const char* szWord, Number &number)
{
    number.m_i32NumberSize = strlen(szWord);
    number.m_szNumber = new char[number.m_i32NumberSize + 1];
    number.m_szWord = new char[number.m_i32NumberSize + 1];
    strcpy(number.m_szWord, szWord);
    char *sTmpNumber = number.m_szNumber;
    while (*szWord)
    {
        *sTmpNumber++ = aLettersNumbersMap[(*szWord++) - 'a'];
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
    if (!(*szTelephoneNumber))
    {
        return true;
    }
    std::list<Number> lMinNumbers;
    for (int32_t i = 0; i < i32NumbersCount; ++i)
    {
        std::list<Number> lTmpNumbers;
        if ((i32TelephoneNumberSize >= pNumbers[i].m_i32NumberSize) &&
            !strncmp(szTelephoneNumber, pNumbers[i].m_szNumber, pNumbers[i].m_i32NumberSize))
        {
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
                    lMinNumbers = std::move(lTmpNumbers);
                    lMinNumbers.push_back(pNumbers[i]);
                    if (1 == lMinNumbers.size())
                    {
                        break;
                    }
                }
            }
        }
    }
    bool result = !lMinNumbers.empty();
    if (result)
    {
        lNumbers.splice(lNumbers.end(), lMinNumbers);
    }
    return result;
}

std::list<Number> _GetSolution(char* szTelephoneNumber, int32_t i32NumbersCount, Number* pNumbers)
{
    static Number noSolution = { 12, "No solution.", "No solution." };

    int32_t i32TelephoneNumberSize = strlen(szTelephoneNumber);

    std::list<Number> lMinNumbers;
    _RecursiveGetSolution(szTelephoneNumber, i32TelephoneNumberSize, i32NumbersCount, pNumbers, lMinNumbers);
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
    fscanf(in, "%s", szTelephoneNumber);

    while (strncmp(szTelephoneNumber, "-1", sizeof("-1")))
    {
        int32_t i32WordsCount = 0;
        fscanf(in, "%d", &i32WordsCount);

        char word[51];
        Number* pNumbers = new Number[i32WordsCount];

        for (int32_t i = 0; i < i32WordsCount; ++i)
        {
            fscanf(in, "%s", word);
            _FormNumber(word, pNumbers[i]);
        }

        // TODO: solve
        std::list<Number> lNumbers = _GetSolution(szTelephoneNumber, i32WordsCount, pNumbers);
        bool first = true;
        for (auto numberIt = lNumbers.rbegin(); numberIt != lNumbers.rend(); ++numberIt)
        {
            if (!first)
                fprintf_s(out, " ");
            fprintf_s(out, "%s", numberIt->m_szWord);
            first = false;
        }
        fprintf_s(out, "\n");

        for (int32_t i = 0; i < i32WordsCount; ++i)
        {
            delete[] pNumbers[i].m_szWord;
            delete[] pNumbers[i].m_szNumber;
        }
        delete[] pNumbers;

        // get telephone number
        fscanf(in, "%s", &szTelephoneNumber);
    }

    return -1;
}
