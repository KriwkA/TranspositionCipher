#ifndef CRYPTOGRAPH_H
#define CRYPTOGRAPH_H

class Cryptograph
{
public:
    Cryptograph();
    virtual ~Cryptograph();

    virtual void encrypt(const char* keyString, const char* inFilePath, const char* outFilePath);
    virtual void decrypt(const char* keyString, const char* inFilePath, const char* outDirPath);

    inline long long getProgress() const { return m_progress; }

private:
    long long m_progress;
};

#endif // CRYPTOGRAPH_H
