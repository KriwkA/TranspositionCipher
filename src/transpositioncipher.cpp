#include "transpositioncipher.h"

#include "file.h"
#include "cryptkey.h"
#include <cstring>
#include <exception>


TranspositionCipher::TranspositionCipher()
    : AbstractCipher()
    , m_pKey(0)
{

}

TranspositionCipher::~TranspositionCipher()
{

}

void TranspositionCipher::encrypt(const char *keyString, const char *inFilePath, const char* outFilePath)
{



}

void TranspositionCipher::decrypt(const char *keyString, const char *inFilePath, const char* outFilePath)
{


}

void TranspositionCipher::openFiles(const char *keyString, const char *inFilePath, const char* outFilePath)
{

    m_pInputFile = new File(inFilePath);
    m_pOutputFile = new File(outFilePath);

    try
    {
        int inFlag = (int)File::OpenMode::ReadOnly | (int)File::OpenMode::Binary;
        int outFlag = (int)File::OpenMode::ReadWrite | (int)File::OpenMode::Binary;
        m_pInputFile->open((File::OpenMode)inFlag);
        m_pOutputFile->open((File::OpenMode)outFlag);
        m_pKey = new CryptKey(m_pInputFile->getSize(), keyString);
    }
    catch(const std::exception& e)
    {
        char error[256] = "Open ";
        strcat(error, (m_pInputFile->isOpen() ? "output" : "input"));
        strcat(error, " file error: ");
        strcat(error, e.what());

        throw std::exception(error);
    }
}

void TranspositionCipher::closeFiles()
{
    if(m_pInputFile)
    {
        m_pInputFile->close();
        delete m_pInputFile;
    }

    if(m_pOutputFile)
    {
        m_pOutputFile->close();
        delete m_pOutputFile;
    }

    if(m_pKey)
    {
        delete m_pKey;
    }
}
