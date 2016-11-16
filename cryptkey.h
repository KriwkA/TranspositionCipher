#ifndef CRYPTKEY_H
#define CRYPTKEY_H


class CryptKey
{
public:
    explicit CryptKey(int keyLength, const char* seedString = "defaultSeed");
    virtual ~CryptKey();

    inline const int* getRowKey() const { return m_pRowKey; }
    inline const int* getColKey() const { return m_pColKey; }
    inline int getKeyLength() const { return m_keyLength; }

private:
    static int generateSeed(const char* seedString);


private:
    int* m_pRowKey;
    int* m_pColKey;
    int m_keyLength;
};

#endif // CRYPTKEY_H
