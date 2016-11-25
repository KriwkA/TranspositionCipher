#ifndef CRYPTKEY_H
#define CRYPTKEY_H

#include <cstdint>

class CryptKey
{
public:
    explicit CryptKey(uint64_t fileLength, const char* seedString = "defaultSeed");
    virtual ~CryptKey();

    inline const uint64_t* getRowKey() const { return m_pRowKey; }
    inline const uint64_t* getColKey() const { return m_pColKey; }
    inline const uint64_t* getRowDecryptKey() const { return m_pRowDecryptKey; }
    inline const uint64_t* getColDecryptKey() const { return m_pColDecryptKey; }

    inline uint64_t getRowKeyLength() const { return m_rowKeyLength; }
    inline uint64_t getColKeyLength() const { return m_colKeyLength; }

    uint64_t getEncryptedIndex(uint64_t baseIndex) const;
    uint64_t getBaseIndex(uint64_t encryptedIndex) const;

private:
    static uint64_t getIndex(uint64_t baseIndex,
                             uint64_t numberRow, uint64_t numberCol,
                             const uint64_t* rowArr,
                             const uint64_t* colArr);

    void calculateKeyLength(uint64_t fileLength);
    void allocateKeys();
    void freeKeys();
    void initKeys();
    void mixKeys(const char *seedString);
    void generateDecryptKeys();

private:
    uint64_t* m_pRowKey;
    uint64_t* m_pColKey;

    uint64_t* m_pRowDecryptKey;
    uint64_t* m_pColDecryptKey;

    uint64_t m_rowKeyLength;
    uint64_t m_colKeyLength;
};

#endif // CRYPTKEY_H
