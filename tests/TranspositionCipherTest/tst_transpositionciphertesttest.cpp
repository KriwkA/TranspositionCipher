#include <QString>
#include <QtTest>

class TranspositionCipherTestTest : public QObject
{
    Q_OBJECT

public:
    TranspositionCipherTestTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

};

TranspositionCipherTestTest::TranspositionCipherTestTest()
{
}

void TranspositionCipherTestTest::initTestCase()
{
}

void TranspositionCipherTestTest::cleanupTestCase()
{
}



QTEST_APPLESS_MAIN(TranspositionCipherTestTest)

#include "tst_transpositionciphertesttest.moc"
