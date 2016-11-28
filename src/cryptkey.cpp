#include "cryptkey.h"
#include <cmath>
#include <random>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

CryptKey::CryptKey(uint64_t baseFileLength, const char *seedString)
    : m_fileLength(baseFileLength)
{
    resetEncryptIndex();
    resetDencryptIndex();
    calculateKeyLength();
    allocateKeys();
    initKeys();
    mixKeys(seedString);
    generateDecryptKeys();
}

CryptKey::~CryptKey()
{
    freeKeys();
}

uint64_t CryptKey::hasNextEncryptIndex() const
{
    return MAX(m_cryptSeqLength - m_currentEncryptIndex, 0);
}

uint64_t CryptKey::hasNextDecryptIndex() const
{
    return MAX(m_fileLength - m_currentDecryptIndex, 0);
}

uint64_t CryptKey::nextEncryptIndex()
{
    return getEncryptedIndex(m_currentEncryptIndex++);
}

uint64_t CryptKey::nextDecryptIndex()
{
    return getDecryptedIndex(m_currentDecryptIndex++);
}

uint64_t CryptKey::getEncryptedIndex(const uint64_t& baseIndex) const
{
    return getEncryptedIndex(baseIndex / m_colKeyLength, baseIndex % m_colKeyLength);
}

uint64_t CryptKey::getDecryptedIndex(const uint64_t& encryptedIndex) const
{
    return getDecryptedIndex(encryptedIndex / m_colKeyLength, encryptedIndex % m_colKeyLength);
}

uint64_t CryptKey::getEncryptedIndex(uint64_t row, uint64_t col) const
{
    return m_pRowKey[row] * m_colKeyLength + m_pColKey[col];
}

uint64_t CryptKey::getDecryptedIndex(uint64_t row, uint64_t col) const
{
    return m_pRowDecryptKey[row] * m_colKeyLength + m_pColDecryptKey[col];
}

uint64_t CryptKey::getEncryptedRowIndex(uint64_t row) const
{
    return m_pRowKey[row] * m_colKeyLength;
}

uint64_t CryptKey::getDecryptedRowIndex(uint64_t row) const
{
    return m_pRowDecryptKey[row] * m_colKeyLength;
}

void CryptKey::calculateKeyLength()
{
    m_rowKeyLength = m_colKeyLength = (uint64_t)std::sqrt(m_fileLength);
    if(m_rowKeyLength * m_colKeyLength < m_fileLength)
    {
        m_rowKeyLength++;
        m_colKeyLength++;
    }
    m_cryptSeqLength = m_rowKeyLength * m_colKeyLength;
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
    if(!(m_rowKeyLength || m_colKeyLength))
        return;

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
