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
    closeFiles();
    freeKey();
}

void TranspositionCipher::encrypt(const char *keyString, const char *inFilePath, const char* outFilePath)
{
}

void TranspositionCipher::decrypt(const char *keyString, const char *inFilePath, const char* outFilePath)
{
}

void TranspositionCipher::openFiles(const char *inFilePath, const char* outFilePath)
{
    m_pInputFile = new File(inFilePath);
    m_pOutputFile = new File(outFilePath);

    try
    {
        int inFlag = (int)File::OpenMode::ReadOnly | (int)File::OpenMode::Binary;
        int outFlag = (int)File::OpenMode::ReadWrite | (int)File::OpenMode::Binary;
        m_pInputFile->open((File::OpenMode)inFlag);
        m_pOutputFile->open((File::OpenMode)outFlag);
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
        m_pInputFile = 0;
    }

    if(m_pOutputFile)
    {
        m_pOutputFile->close();
        delete m_pOutputFile;
        m_pOutputFile = 0;
    }
}

void TranspositionCipher::initKey(const char *keyString, WorkType type)
{
    uint64_t baseFileLength;
    if(type == WorkType::ENCRYPT)
        baseFileLength = m_pInputFile->getSize();
    else
        baseFileLength = m_pInputFile->readLongLong();

    m_pKey = new CryptKey(baseFileLength, keyString);
}

void TranspositionCipher::freeKey()
{
    if(m_pKey)
    {
        delete m_pKey;
        m_pKey = 0;
    }
}
