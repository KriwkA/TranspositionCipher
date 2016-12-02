#ifndef CRYPTKEY_H
#define CRYPTKEY_H

#include <cstdint>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

class CryptKey
{
public:
    explicit CryptKey(uint64_t baseFileLength, const char* seedString = "defaultSeed");
    virtual ~CryptKey();

    inline uint64_t getCryptSeqLength() const { return m_cryptSeqLength; }
    inline uint64_t getRowKeyLength() const { return m_rowKeyLength; }
    inline uint64_t getColKeyLength() const { return m_colKeyLength; }

    inline uint64_t rowKeyAt(uint64_t pos) const { return m_pRowKey[pos]; }
    inline uint64_t colKeyAt(uint64_t pos) const { return m_pColKey[pos]; }

    inline uint64_t rowDecryptKeyAt(uint64_t pos) const { return m_pRowDecryptKey[pos]; }
    inline uint64_t colDecryptKeyAt(uint64_t pos) const { return m_pColDecryptKey[pos]; }

    uint64_t getEncryptedIndex(const uint64_t& baseIndex) const;
    uint64_t getDecryptedIndex(const uint64_t& encryptedIndex) const;

    inline uint64_t getEncryptedIndex(uint64_t row, uint64_t col) const { return m_pRowKey[row] * m_colKeyLength + m_pColKey[col]; }
    inline uint64_t getDecryptedIndex(uint64_t row, uint64_t col) const { return m_pRowDecryptKey[row] * m_colKeyLength + m_pColDecryptKey[col]; }

    inline uint64_t getEncryptedRowIndex(uint64_t row) const { return m_pRowKey[row] * m_colKeyLength; }
    inline uint64_t getDecryptedRowIndex(uint64_t row) const { return m_pRowDecryptKey[row] * m_colKeyLength; }

    inline uint64_t hasNextEncryptIndex() const { return MAX(m_cryptSeqLength - m_currentEncryptIndex, 0); }
    inline uint64_t hasNextDecryptIndex() const { return MAX(m_fileLength - m_currentDecryptIndex, 0); }

    uint64_t nextEncryptIndex();
    uint64_t nextDecryptIndex();

    inline void resetEncryptIndex() { m_currentEncryptIndex = 0; }
    inline void resetDencryptIndex() { m_currentDecryptIndex = 0; }

private:
    void calculateKeyLength();
    void allocateKeys();
    void freeKeys();
    void initKeys();
    void mixKeys(const char *seedString);
    void generateDecryptKeys();

    uint64_t m_currentEncryptIndex;
    uint64_t m_currentDecryptIndex;

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
