#include "transpositioncipher.h"

#include "file.h"
#include "cryptkey.h"
#include <exception>


void TranspositionCipher::encrypt(const char *keyString, File *inFile, File *outFile)
{
    try
    {
        prepareFiles(keyString, inFilePath, outFilePath);
    }
    catch (const std::exception& e)
    {

    }

    closeFiles();

}

void TranspositionCipher::decrypt(const char *keyString, File *inFilePath, File *outFile)
{
    try
    {
        prepareFiles(keyString, inFilePath, outFilePath);
    }
    catch (const std::exception& e)
    {

    }

    closeFiles();
}

void TranspositionCipher::prepareFiles(const char *keyString, File *inFilePath, File *outFile)
{
    m_pKey = new CryptKey(inputFile.getSize(), keyString);
    m_pInputFile = new File(inFilePath);
    m_pOutputFile = new File(outFile);

    m_pInputFile->open(File::OpenMode::ReadOnly | File::OpenMode::Binary);
    m_pOutputFile->open(File::OpenMode::ReadWrite | File::OpenMode::Binary);
}

void TranspositionCipher::closeFiles()
{
    m_pInputFile->close();
    m_pOutputFile->close();

    delete m_pOutputFile;
    delete m_pInputFile;
    delete m_pKey;
}
