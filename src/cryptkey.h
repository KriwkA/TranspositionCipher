#ifndef CRYPTKEY_H
#define CRYPTKEY_H


class CryptKey
{
public:
    explicit CryptKey(long long fileLength, const char* seedString = "defaultSeed");
    virtual ~CryptKey();

    inline const unsigned long long* getRowKey() const { return m_pRowKey; }
    inline const unsigned long long* getColKey() const { return m_pColKey; }
    inline unsigned long long getKeyLength() const { return m_keyLength; }

    unsigned long long getEncryptedIndex(unsigned long long baseIndex) const;
    unsigned long long getBaseIndex(unsigned long long encryptedIndex) const;

private:
    static int generateSeed(const char* seedString);
    static unsigned long long getIndex(unsigned long long baseIndex,
                                       unsigned long long length,
                                       const unsigned long long* rowArr,
                                       const unsigned long long* colArr);
    void calculateKeyLength(unsigned long long fileLength);

private:
    unsigned long long* m_pRowKey;
    unsigned long long* m_pColKey;

    unsigned long long* m_pRowDecryptKey;
    unsigned long long* m_pColDecryptKey;

    unsigned long long m_keyLength;
};

#endif // CRYPTKEY_H
