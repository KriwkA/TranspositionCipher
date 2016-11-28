#ifndef TRANSPOSITIONCIPHER_H
#define TRANSPOSITIONCIPHER_H

#include "abstractcipher.h"

#include <cstdint>

class CryptKey;

class TranspositionCipher : public AbstractCipher
{
public:
    TranspositionCipher();
    virtual ~TranspositionCipher();

    virtual void encrypt(const char *keyString, const char *inFilePath, const char* outFilePath);
    virtual void decrypt(const char *keyString, const char *inFilePath, const char* outFilePath);

    inline virtual void stop() override { m_bIsWorking = false; }

private:
    void openFiles(const char *inFilePath, const char* outFilePath);
    void closeFiles();

    void initKey(const char *keyString, uint64_t fileLength);
    void freeKey();

    File* m_pInputFile;
    File* m_pOutputFile;
    CryptKey* m_pKey;

    volatile bool m_bIsWorking;


};

#endif // TRANSPOSITIONCIPHER_H
