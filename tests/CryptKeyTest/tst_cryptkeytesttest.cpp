#include <QString>
#include <QtTest>

#include "../../src/cryptkey.h"

class CryptKeyTestTest : public QObject
{
    Q_OBJECT

public:
    CryptKeyTestTest(){}

private:
    bool testKey(uint64_t length, const char* keyStr)
    {
        CryptKey key(length, keyStr);

        char* basestr = (char*)calloc((length + 1), sizeof(char));
        char* encryptedstr = (char*)calloc((length + 1),  sizeof(char));
        char* decryptedstr = (char*)calloc((length + 1),  sizeof(char));

        for(int i = 0; i < length; ++i)
            basestr[i] = (char) (rand() % 10 + int('0'));

        for(int i = 0; i < length; ++i)
            encryptedstr[i] = basestr[key.getEncryptedIndex(i)];

        for(int i = 0; i < length; ++i)
            decryptedstr[i] = encryptedstr[key.getBaseIndex(i)];

        bool testRes = !strcmp(basestr, decryptedstr);
        free(basestr);
        free(encryptedstr);
        free(decryptedstr);
        return testRes;
    }

private Q_SLOTS:
    void initTestCase(){}
    void cleanupTestCase(){}

    void test1();
    void test2();
    void test3();
    void test4();
    void test5();

};

void CryptKeyTestTest::test1()
{
    QVERIFY(testKey(4, "Test1"));
}

void CryptKeyTestTest::test2()
{
    QVERIFY(testKey(9, "Test2"));
}

void CryptKeyTestTest::test3()
{
    QVERIFY(testKey(16, "Test3"));
}

void CryptKeyTestTest::test4()
{
    QVERIFY(testKey(25, "Test4"));
}

void CryptKeyTestTest::test5()
{
    QVERIFY(testKey(36, "Test5"));
}

QTEST_APPLESS_MAIN(CryptKeyTestTest)

#include "tst_cryptkeytesttest.moc"
