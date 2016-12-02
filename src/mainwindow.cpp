#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "transpositioncipher.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_encrypt_clicked()
{
    CipherDialog* cipher = new CipherDialog(new TranspositionCipher(),
                                            CipherDialog::Type::Encrypt,
                                            getCryptInfo(), this);
    cipher->show();
}

void MainWindow::on_decrypt_clicked()
{
    CipherDialog* cipher = new CipherDialog(new TranspositionCipher(),
                                            CipherDialog::Type::Decrypt,
                                            getCryptInfo(), this);
    cipher->show();
    cipher->exec();
}

CipherDialog::CryptInfo MainWindow::getCryptInfo() const
{
    CipherDialog::CryptInfo info;
    info.inputFile = ui->inputFilePath->text();
    info.outputFile = ui->outputFilePath->text();
    info.password = ui->cryptKey->text();
    return info;
}

void MainWindow::on_cryptKey_textChanged(const QString &arg1)
{
    if(arg1.length() < 5)
    {
        ui->encrypt->setEnabled(false);
        ui->decrypt->setEnabled(false);
    }
    else
    {
        ui->encrypt->setEnabled(true);
        ui->decrypt->setEnabled(true);
    }
}


