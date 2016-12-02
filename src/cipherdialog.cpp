#include "cipherdialog.h"
#include "ui_cipherdialog.h"

#include "abstractcipher.h"

#include <thread>

#include <QMessageBox>

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

    m_pWorkThread = new std::thread(&CipherDialog::work, this, type, info);

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
    killTimer(m_checkProgressTimerId);
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

void CipherDialog::work(CipherDialog::Type type, const CipherDialog::CryptInfo &cryptInfo)
{
    try
    {
        switch (type)
        {
        case Type::Encrypt: encrypt(cryptInfo); break;
        case Type::Decrypt: decrypt(cryptInfo); break;
        default: break;
        }
    }
    catch(const std::exception& e)
    {
        QMetaObject::invokeMethod(this, "showError", Qt::QueuedConnection,  Q_ARG(QString, QString(e.what())));
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

void CipherDialog::showError(const QString &errorString)
{
    QMessageBox* error = new QMessageBox(this);
    error->setWindowTitle("Cipher ERROR");
    error->setText(errorString);
    error->show();
    error->exec();
    emit done();
}

void CipherDialog::on_cancel_clicked()
{
    this->close();
}
