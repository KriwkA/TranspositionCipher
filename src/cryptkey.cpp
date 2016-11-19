#include "cryptkey.h"
#include <algorithm>
#include <string>
#include <cmath>

CryptKey::CryptKey(long long fileLength, const char *seedString)

{

    calculateKeyLength(fileLength);

    m_pRowKey = (unsigned long long*)calloc(m_keyLength, sizeof(long long));
    m_pColKey = (unsigned long long*)calloc(m_keyLength, sizeof(long long));

    m_pRowDecryptKey = (unsigned long long*)calloc(m_keyLength, sizeof(long long));
    m_pColDecryptKey = (unsigned long long*)calloc(m_keyLength, sizeof(long long));

    for(int i = 0; i < m_keyLength; ++i)
    {
        m_pRowKey[i] = i;
        m_pColKey[i] = i;
    }

    int seed = generateSeed(seedString);
    srand(seed);

    for(unsigned long long i = m_keyLength - 1; i > 0; --i)
    {
        std::swap(m_pRowKey[i], m_pRowKey[rand() % i]);
        std::swap(m_pColKey[i], m_pColKey[rand() % i]);
    }

    for(int i = 0; i < m_keyLength; ++i)
    {
        m_pRowDecryptKey[m_pRowKey[i]] = i;
        m_pColDecryptKey[m_pColKey[i]] = i;
    }

}

CryptKey::~CryptKey()
{
    free(m_pRowKey);
    free(m_pColKey);
}

unsigned long long CryptKey::getEncryptedIndex(unsigned long long baseIndex) const
{
    return getIndex(baseIndex, m_keyLength, m_pRowKey, m_pColKey);
}

unsigned long long CryptKey::getBaseIndex(unsigned long long encryptedIndex) const
{
    return getIndex(encryptedIndex, m_keyLength, m_pRowDecryptKey, m_pColDecryptKey);
}

int CryptKey::generateSeed(const char *seedString)
{
    return (int)std::hash<const char*>().operator()(seedString);
}

unsigned long long CryptKey::getIndex(unsigned long long baseIndex,
                                      unsigned long long length,
                                      const unsigned long long *rowArr,
                                      const unsigned long long *colArr)
{
    unsigned long long row = rowArr[baseIndex / length];
    unsigned long long col = colArr[baseIndex % length];
    return row * length + col;
}

void CryptKey::calculateKeyLength(unsigned long long fileLength)
{
    m_keyLength = (unsigned long long)std::sqrt(fileLength);
    if(m_keyLength * m_keyLength < fileLength)
        m_keyLength++;
}
