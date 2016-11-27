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

private:
    void openFiles(const char *inFilePath, const char* outFilePath);
    void closeFiles();

    enum class WorkType{ ENCRYPT, DECRYPT };

    void mixBuffer(WorkType type, char* inBuf, char* outBuf) const;
    void work(WorkType type, const char *keyString, const char *inFilePath, const char* outFilePath);

    void initKey(const char *keyString, WorkType type);
    void freeKey();

    File* m_pInputFile;
    File* m_pOutputFile;
    CryptKey* m_pKey;



};

#endif // TRANSPOSITIONCIPHER_H
