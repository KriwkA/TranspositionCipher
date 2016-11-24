#include <QString>
#include <QtTest>

class FileTestTest : public QObject
{
    Q_OBJECT

public:
    FileTestTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
};

FileTestTest::FileTestTest()
{
}

void FileTestTest::initTestCase()
{

}

void FileTestTest::cleanupTestCase()
{

}



QTEST_APPLESS_MAIN(FileTestTest)

#include "tst_filetesttest.moc"
