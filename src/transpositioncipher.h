#ifndef TRANSPOSITIONCIPHER_H
#define TRANSPOSITIONCIPHER_H

#include "cryptograph.h"


class CryptKey;

class TranspositionCipher : public Cryptograph
{
public:


    virtual void encrypt(const char *keyString, File *inFile, File *outFile);
    virtual void decrypt(const char *keyString, File *inFile, File *outFile);

private:
    void prepareFiles(const char *keyString, File *inFile, File *outFile);
    void closeFiles();

    File* m_pInputFile;
    File* m_pOutputFile;
    CryptKey* m_pKey;


};

#endif // TRANSPOSITIONCIPHER_H
