#ifndef TRANSPOSITIONCIPHER_H
#define TRANSPOSITIONCIPHER_H

#include "abstractcipher.h"

class CryptKey;

class TranspositionCipher : public AbstractCipher
{
public:
    TranspositionCipher();
    virtual ~TranspositionCipher();

    virtual void encrypt(const char *keyString, const char *inFilePath, const char* outFilePath);
    virtual void decrypt(const char *keyString, const char *inFilePath, const char* outFilePath);

private:
    void openFiles(const char *keyString, const char *inFilePath, const char* outFilePath);
    void closeFiles();

    File* m_pInputFile;
    File* m_pOutputFile;
    CryptKey* m_pKey;

};

#endif // TRANSPOSITIONCIPHER_H
