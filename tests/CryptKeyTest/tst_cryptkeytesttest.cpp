#include <QString>
#include <QtTest>

#include "../../src/cryptkey.h"

class CryptKeyTestTest : public QObject
{
    Q_OBJECT

public:
    CryptKeyTestTest(){}

private:
    bool testKey(uint64_t length, const char* encStr, const char* decStr)
    {

        CryptKey enckey(length, encStr);
        CryptKey deckey(length, decStr);

        char* basestr = (char*)calloc((length + 1), sizeof(char));
        char* encryptedstr = (char*)calloc((enckey.getCryptSeqLength() + 1),  sizeof(char));
        char* decryptedstr = (char*)calloc((length + 1),  sizeof(char));

        for(uint64_t i = 0; i < length; ++i)
            basestr[i] = (char) (rand() % 10 + int('0'));

        uint64_t pos = 0;

        uint64_t index;

        while(enckey.hasNextEncryptIndex())
        {
            index = enckey.nextEncryptIndex();
            encryptedstr[pos++] = index != uint64_t(-1) ? basestr[index] : char(rand() % 100 + 48);
        }

        pos = 0;
        while(deckey.hasNextDecryptIndex())
            decryptedstr[pos++] = encryptedstr[deckey.nextDecryptIndex()];

        bool testRes = !strcmp(basestr, decryptedstr);
        free(basestr);
        free(encryptedstr);
        free(decryptedstr);
        return testRes;
    }

    bool testWithRandKey(uint64_t length)
    {
        uint64_t keyStrLength = 15;
        char* encStr = (char*)calloc(keyStrLength + 1, sizeof(char));
        char* decStr = (char*)calloc(keyStrLength + 1, sizeof(char));

        for(int i = 0; i < keyStrLength; ++i)
        {
            encStr[i] = decStr[i] = (char) (rand() % 10 + int('0'));
        }

        bool testRes = testKey(length, encStr, decStr);
        free(encStr);
        free(decStr);

        return testRes;
    }

    bool testKey(uint64_t length, const char *keyStr)
    {
        uint64_t keyStrLength = strlen(keyStr);
        char* encStr = (char*)calloc(keyStrLength + 1, sizeof(char));
        char* decStr = (char*)calloc(keyStrLength + 1, sizeof(char));

        for(int i = 0; i < keyStrLength; ++i)
        {
            encStr[i] = decStr[i] = keyStr[i];
        }

        bool testRes = testKey(length, encStr, decStr);
        free(encStr);
        free(decStr);

        return testRes;
    }

private Q_SLOTS:
    void initTestCase(){}
    void cleanupTestCase(){}

    void test1()      { QVERIFY(testWithRandKey(0)); }
    void test2()      { QVERIFY(testWithRandKey(1)); }
    void test3()      { QVERIFY(testWithRandKey(2)); }
    void test4()      { QVERIFY(testWithRandKey(3)); }
    void test5()      { QVERIFY(testWithRandKey(4)); }
    void test6()      { QVERIFY(testWithRandKey(5)); }
    void test7()      { QVERIFY(testWithRandKey(6)); }
    void test8()      { QVERIFY(testWithRandKey(7)); }
    void test9()      { QVERIFY(testWithRandKey(8)); }
    void test10()     { QVERIFY(testWithRandKey(9)); }
    void test11()     { QVERIFY(testWithRandKey(10)); }
    void test12()     { QVERIFY(testWithRandKey(11)); }
    void test13()     { QVERIFY(testWithRandKey(12)); }
    void test14()     { QVERIFY(testWithRandKey(13)); }
    void test15()     { QVERIFY(testWithRandKey(14)); }
    void test16()     { QVERIFY(testWithRandKey(15)); }
    void test17()     { QVERIFY(testWithRandKey(16)); }
    void test18()     { QVERIFY(testWithRandKey(25)); }
    void test19()     { QVERIFY(testWithRandKey(36)); }
    void test20()     { QVERIFY(testWithRandKey(50)); }
    void test21()     { QVERIFY(testWithRandKey(1000000)); }
    void test22()     { QVERIFY(testWithRandKey(1231000)); }
    void test23()     { QVERIFY(testWithRandKey(1111000)); }
    void test24()     { QVERIFY(testWithRandKey(1004000)); }
    void test25()     { QVERIFY(testWithRandKey(1001000)); }

};




QTEST_APPLESS_MAIN(CryptKeyTestTest)

#include "tst_cryptkeytesttest.moc"
