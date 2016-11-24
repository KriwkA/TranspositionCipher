#include <QString>
#include <QtTest>

#include <cstring>
#include <exception>

#include "../../src/file.h"

class FileTestTest : public QObject
{
    Q_OBJECT

public:
    FileTestTest(){}

private Q_SLOTS:
    void initTestCase(){}
    void cleanupTestCase(){}


    void openNotExistsFileTest();
    void readWriteFileTest();


private:
    File::OpenMode readBin = (File::OpenMode)((int)File::OpenMode::ReadOnly | (int)File::OpenMode::Binary);
    File::OpenMode writeBin = (File::OpenMode)((int)File::OpenMode::ReadWrite | (int)File::OpenMode::Binary);

};


void FileTestTest::openNotExistsFileTest()
{
    File file("not_exists_file.txt");

    try
    {
        file.open(readBin);
        QFAIL("Open not exists file without exception");
    }
    catch(const std::exception& e)
    {
        Q_UNUSED(e);
        file.close();
    }

}

void FileTestTest::readWriteFileTest()
{
    File file("write_test.txt");

    try
    {
        file.open(writeBin);

        for(int i = 0; i < 10; ++i)
            file.writeByte(char(i + (int)'0'));

        file.close();

        file.open(readBin);
        char letter;
        for(int i = 9; i >= 0; --i)
        {
            letter = file.readByte(i);
            QCOMPARE(i, (int)letter - (int)'0');
        }


        try
        {
            letter = file.readByte(10);
            QFAIL("no read bad byte exception");
        }
        catch(const std::exception& e)
        {
            Q_UNUSED(e);
        }

    }
    catch(const std::exception& e)
    {
        QFAIL(e.what());
    }

}

QTEST_APPLESS_MAIN(FileTestTest)

#include "tst_filetesttest.moc"
