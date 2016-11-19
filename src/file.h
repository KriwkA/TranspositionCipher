#ifndef FILE_H
#define FILE_H

#include <cstdio>

class File
{
public:

    enum class OpenMode
    {
        ReadOnly = 0b0001,
        ReadWrite = 0b0010,
        Append = 0b0100,
        Binary = 0b1000
    };

    File();
    File(const char* filePath);
    ~File();

    void setPath(const char* filePath);

    void open(OpenMode openMode);
    void open(const char* filePath, OpenMode openMode);

    void close();

    char readByte();
    char readByte(unsigned long long pos);
    void writeByte(char byte);

    long long getSize();

    inline bool isOpen() const { return (bool)m_pStream; }



private:
    void clearPath();
    void checkSize();
    char getch();


private:
    FILE* m_pStream;
    char* m_path;
    unsigned long long m_size;


};

#endif // FILE_H
