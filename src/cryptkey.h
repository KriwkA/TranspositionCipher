#ifndef CRYPTKEY_H
#define CRYPTKEY_H

#include <cstdint>

class CryptKey
{
public:
    explicit CryptKey(uint64_t baseFileLength, const char* seedString = "defaultSeed");
    virtual ~CryptKey();

    uint64_t hasNextEncryptIndex() const;
    uint64_t hasNextDecryptIndex() const;

    uint64_t nextEncryptIndex();
    uint64_t nextDecryptIndex();

    inline void resetEncryptIndex() { m_currentEncryptIndex = 0; }
    inline void resetDencryptIndex() { m_currentDecryptIndex = 0; }

    inline uint64_t getCryptSeqLength() const { return m_cryptSeqLength; }


private:
    uint64_t m_currentEncryptIndex;
    uint64_t m_currentDecryptIndex;


private:

    static uint64_t getIndex(uint64_t baseIndex,
                             uint64_t numberRow, uint64_t numberCol,
                             const uint64_t* rowArr,
                             const uint64_t* colArr);


    uint64_t getEncryptedIndex(uint64_t baseIndex) const;
    uint64_t getBaseIndex(uint64_t encryptedIndex) const;

    void calculateKeyLength();
    void allocateKeys();
    void freeKeys();
    void initKeys();
    void mixKeys(const char *seedString);
    void generateDecryptKeys();

private:
    uint64_t m_fileLength;

    uint64_t* m_pRowKey;
    uint64_t* m_pColKey;

    uint64_t* m_pRowDecryptKey;
    uint64_t* m_pColDecryptKey;

    uint64_t m_rowKeyLength;
    uint64_t m_colKeyLength;
    uint64_t m_cryptSeqLength;
};

#endif // CRYPTKEY_H
