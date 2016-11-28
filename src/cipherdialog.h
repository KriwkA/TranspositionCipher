#ifndef CIPHERDIALOG_H
#define CIPHERDIALOG_H

#include <QDialog>

namespace Ui {
class CipherDialog;
}

namespace std
{
class thread;
}

class AbstractCipher;

class CipherDialog : public QDialog
{
    Q_OBJECT

public:
    enum class Type {Encrypt, Decrypt};
    struct CryptInfo
    {
        QString password;
        QString inputFile;
        QString outputFile;
    };

    explicit CipherDialog(AbstractCipher* cipher, Type type, const CryptInfo& info, QWidget *parent = 0, bool autoDelCipher = true);
    ~CipherDialog();

signals:
    void done();

private slots:
    void onDone();

    void on_cancel_clicked();

private:
    virtual void timerEvent(QTimerEvent *event) override;

    void encrypt(const CryptInfo& cryptInfo);
    void decrypt(const CryptInfo& cryptInfo);

    Ui::CipherDialog *ui;
    AbstractCipher* m_cipher;

    bool m_bAutoDeleteCipher;
    int m_checkProgressTimerId;

    std::thread* m_pWorkThread;
};

#endif // CIPHERDIALOG_H
