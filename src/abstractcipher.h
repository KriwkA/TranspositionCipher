#ifndef CRYPTOGRAPH_H
#define CRYPTOGRAPH_H

class File;

class AbstractCipher
{
public:
    AbstractCipher();
    virtual ~AbstractCipher();

    virtual void encrypt(const char *keyString, const char *inFilePath, const char* outFilePath) = 0;
    virtual void decrypt(const char *keyString, const char *inFilePath, const char* outFilePath) = 0;

    inline double getProgress() const { return m_progress; }

protected:
    inline void setProgress(double value) { m_progress = value; }

private:
    double m_progress;
};

#endif // CRYPTOGRAPH_H
