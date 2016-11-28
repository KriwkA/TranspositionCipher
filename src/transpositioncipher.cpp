#include "transpositioncipher.h"

#include "file.h"
#include "cryptkey.h"
#include <cstring>
#include <exception>


TranspositionCipher::TranspositionCipher()
    : AbstractCipher()
    , m_pKey(0)
    , m_bIsWorking(false)
{

}

TranspositionCipher::~TranspositionCipher()
{
    closeFiles();
    freeKey();
}

void TranspositionCipher::encrypt(const char *keyString, const char *inFilePath, const char* outFilePath)
{
    if(m_bIsWorking)
        return;
    m_bIsWorking = true;
    openFiles(inFilePath, outFilePath);
    initKey(keyString, m_pInputFile->getSize());
    m_pOutputFile->writeLongLong(m_pInputFile->getSize());

    const uint64_t bufLength = m_pKey->getColKeyLength();
    const uint64_t rowCount = m_pKey->getRowKeyLength();

    char* inBuf = (char*)malloc(bufLength);
    char* outBuf = (char*)malloc(bufLength);

    for(uint64_t index, i = 0; m_bIsWorking && i < rowCount; ++i)
    {
        index = m_pKey->getEncryptedRowIndex(i);
        m_pInputFile->read(inBuf, bufLength, index);
        for(uint64_t i = 0; i < bufLength; ++i)
            outBuf[i] = inBuf[m_pKey->colKeyAt(i)];
        m_pOutputFile->write(outBuf, bufLength);
        setProgress((double)i / (double)rowCount);
    }

    free(inBuf);
    free(outBuf);
    freeKey();
    closeFiles();

    setProgress(1.0);
    m_bIsWorking = false;
}

void TranspositionCipher::decrypt(const char *keyString, const char *inFilePath, const char* outFilePath)
{
    if(m_bIsWorking)
        return;
    m_bIsWorking = true;
    openFiles(inFilePath, outFilePath);
    const uint64_t outLength = m_pInputFile->readLongLong();
    initKey(keyString, outLength);

    const uint64_t bufLength = m_pKey->getColKeyLength();
    const uint64_t rowCount = outLength / bufLength + (outLength % bufLength ? 1 : 0);
    uint64_t lastChunkSize = outLength % bufLength;
    if(!lastChunkSize)
        lastChunkSize = bufLength;


    char* inBuf = (char*)malloc(bufLength);
    char* outBuf = (char*)malloc(bufLength);

    const uint64_t indexShift = sizeof(uint64_t);

    uint64_t cryptLength;

    for(uint64_t index, i = 0; m_bIsWorking && i < rowCount; ++i)
    {
        index = m_pKey->getDecryptedRowIndex(i);
        m_pInputFile->read(inBuf, bufLength, index + indexShift);
        cryptLength = (i != rowCount - 1) ? bufLength : lastChunkSize;
        for(uint64_t i = 0; i < cryptLength; ++i)
            outBuf[i] = inBuf[m_pKey->colDecryptKeyAt(i)];
        m_pOutputFile->write(outBuf, cryptLength);
        setProgress((double)i / (double)rowCount);
    }

    free(inBuf);
    free(outBuf);
    freeKey();
    closeFiles();
    setProgress(1.0);
    m_bIsWorking = false;
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

void TranspositionCipher::initKey(const char *keyString, uint64_t fileLength)
{   
    m_pKey = new CryptKey(fileLength, keyString);
}

void TranspositionCipher::freeKey()
{
    if(m_pKey)
    {
        delete m_pKey;
        m_pKey = 0;
    }
}
