#include "cryptkey.h"
#include <algorithm>
#include <string>
#include <cmath>
#include <random>

CryptKey::CryptKey(uint64_t fileLength, const char *seedString)
{
    calculateKeyLength(fileLength);
    allocateKeys();
    initKeys();
    mixKeys(seedString);
    generateDecryptKeys();
}

CryptKey::~CryptKey()
{
    freeKeys();
}

uint64_t CryptKey::getEncryptedIndex(uint64_t baseIndex) const
{
    return getIndex(baseIndex, m_rowKeyLength, m_colKeyLength, m_pRowKey, m_pColKey);
}

uint64_t CryptKey::getBaseIndex(uint64_t encryptedIndex) const
{
    return getIndex(encryptedIndex, m_rowKeyLength, m_colKeyLength, m_pRowDecryptKey, m_pColDecryptKey);
}

uint64_t CryptKey::getIndex(uint64_t baseIndex,
                            uint64_t numberRow, uint64_t numberCol,
                            const uint64_t *rowArr,
                            const uint64_t *colArr)
{
    uint64_t row = rowArr[baseIndex / numberRow];
    uint64_t col = colArr[baseIndex % numberCol];
    return row * numberRow + col;
}

void CryptKey::calculateKeyLength(uint64_t fileLength)
{
    m_rowKeyLength = m_colKeyLength = (uint64_t)std::sqrt(fileLength);
    if(m_rowKeyLength * m_colKeyLength < fileLength)
    {
        m_rowKeyLength++;
        m_colKeyLength++;
    }
}

void CryptKey::allocateKeys()
{
    m_pRowKey = (uint64_t*)malloc(m_rowKeyLength * sizeof(uint64_t));
    m_pColKey = (uint64_t*)malloc(m_colKeyLength * sizeof(uint64_t));

    m_pRowDecryptKey = (uint64_t*)malloc(m_rowKeyLength * sizeof(uint64_t));
    m_pColDecryptKey = (uint64_t*)malloc(m_colKeyLength * sizeof(uint64_t));
}

void CryptKey::freeKeys()
{
    free(m_pRowKey);
    free(m_pColKey);
    free(m_pRowDecryptKey);
    free(m_pColDecryptKey);
}

void CryptKey::initKeys()
{
    for(uint64_t i = 0; i < m_rowKeyLength; ++i)
        m_pRowKey[i] = i;

    for(uint64_t i = 0; i < m_colKeyLength; ++i)
        m_pColKey[i] = i;

}

void CryptKey::mixKeys(const char *seedString)
{
    std::seed_seq seed(seedString, seedString + strlen(seedString));
    std::minstd_rand0 random(seed);

    for(uint64_t i = m_rowKeyLength - 1; i > 0; --i)
        std::swap(m_pRowKey[i], m_pRowKey[random() % (i + 1)]);

    for(uint64_t i = m_colKeyLength - 1; i > 0; --i)
        std::swap(m_pColKey[i], m_pColKey[random() % (i + 1)]);
}

void CryptKey::generateDecryptKeys()
{
    for(uint64_t i = 0; i < m_rowKeyLength; ++i)
        m_pRowDecryptKey[m_pRowKey[i]] = i;

    for(uint64_t i = 0; i < m_colKeyLength; ++i)
        m_pColDecryptKey[m_pColKey[i]] = i;
}
