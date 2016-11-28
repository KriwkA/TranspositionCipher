#include "cipherdialog.h"
#include "ui_cipherdialog.h"

#include "abstractcipher.h"

#include <thread>

CipherDialog::CipherDialog(AbstractCipher *cipher, Type type, const CryptInfo &info, QWidget *parent, bool autoDelCipher)
    : QDialog(parent)
    , ui(new Ui::CipherDialog)
    , m_cipher(cipher)
    , m_bAutoDeleteCipher(autoDelCipher)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose, true);

    connect(this, SIGNAL(done()),
            this, SLOT(onDone()));

    switch(type)
    {
    case Type::Encrypt:
        m_pWorkThread = new std::thread(&CipherDialog::encrypt, this, info);
        break;

    case Type::Decrypt:
        m_pWorkThread = new std::thread(&CipherDialog::decrypt, this, info);
        break;
    }

    m_checkProgressTimerId = startTimer(13);
}

CipherDialog::~CipherDialog()
{
    if(m_cipher)
    {
        m_cipher->stop();
        m_pWorkThread->join();
        delete m_pWorkThread;
        if(m_bAutoDeleteCipher)
            delete m_cipher;
    }

    delete ui;
}

void CipherDialog::onDone()
{
    ui->cancel->setText("Close");
}

void CipherDialog::timerEvent(QTimerEvent *event)
{
    QDialog::timerEvent(event);

    if(event->timerId() == m_checkProgressTimerId)
    {
        double progress = m_cipher->getProgress();
        ui->progress->setValue(progress * 100);
        if(progress == 1.0)
            emit done();
    }
}

void CipherDialog::encrypt(const CryptInfo& cryptInfo)
{
    m_cipher->encrypt(cryptInfo.password.toStdString().c_str(),
                      cryptInfo.inputFile.toStdString().c_str(),
                      cryptInfo.outputFile.toStdString().c_str());
}

void CipherDialog::decrypt(const CipherDialog::CryptInfo &cryptInfo)
{
    m_cipher->decrypt(cryptInfo.password.toStdString().c_str(),
                      cryptInfo.inputFile.toStdString().c_str(),
                      cryptInfo.outputFile.toStdString().c_str());
}

void CipherDialog::on_cancel_clicked()
{
    this->close();
}
