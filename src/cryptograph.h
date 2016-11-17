#ifndef CRYPTOGRAPH_H
#define CRYPTOGRAPH_H

class File;

class Cryptograph
{
public:
    Cryptograph();
    virtual ~Cryptograph();

    virtual void encrypt(const char *keyString, File *inFilePath, File *outFile) = 0;
    virtual void decrypt(const char *keyString, File *inFilePath, File *outFile) = 0;

    inline long long getProgress() const { return m_progress; }

protected:
    virtual void setProgress(double value) { m_progress = value; }

private:
    double m_progress;
};

#endif // CRYPTOGRAPH_H
