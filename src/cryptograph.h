#ifndef CRYPTOGRAPH_H
#define CRYPTOGRAPH_H

class Cryptograph
{
public:
    Cryptograph();
    virtual ~Cryptograph();

    virtual void encrypt(const char* keyString, const char* inFilePath, const char* outFilePath) = 0;
    virtual void decrypt(const char* keyString, const char* inFilePath, const char* outDirPath) = 0;

    inline long long getProgress() const { return m_progress; }

protected:
    virtual void setProgress(double value) = 0;

private:
    double m_progress;
};

#endif // CRYPTOGRAPH_H
