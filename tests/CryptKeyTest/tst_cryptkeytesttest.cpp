#include <QString>
#include <QtTest>

class CryptKeyTestTest : public QObject
{
    Q_OBJECT

public:
    CryptKeyTestTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

};

CryptKeyTestTest::CryptKeyTestTest()
{
}

void CryptKeyTestTest::initTestCase()
{
}

void CryptKeyTestTest::cleanupTestCase()
{
}


QTEST_APPLESS_MAIN(CryptKeyTestTest)

#include "tst_cryptkeytesttest.moc"
