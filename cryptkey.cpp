#include "cryptkey.h"
#include <algorithm>
#include <string>

CryptKey::CryptKey(int keyLength, const char *seedString)
    : m_keyLength(keyLength)
    , m_pRowKey((int*)calloc(keyLength, sizeof(int)))
    , m_pColKey((int*)calloc(keyLength, sizeof(int)))
{

    for(int i = 0; i < keyLength; ++i)
    {
        m_pRowKey[i] = i;
        m_pColKey[i] = i;
    }

    int seed = generateSeed(seedString);
    srand(seed);

    for(int i = keyLength - 1; i > 0; --i)
    {
        std::swap(m_pRowKey[i], m_pRowKey[rand() % i]);
        std::swap(m_pColKey[i], m_pColKey[rand() % i]);
    }

}

CryptKey::~CryptKey()
{
    free(m_pRowKey);
    free(m_pColKey);
}

int CryptKey::generateSeed(const char *seedString)
{
    return std::hash<const char*>().operator()(seedString);
}
