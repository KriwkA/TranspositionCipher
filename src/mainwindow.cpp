#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "transpositioncipher.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setEnableWorkButtons(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startCipher(CipherDialog::Type type)
{
    CipherDialog* cipher = new CipherDialog(new TranspositionCipher(),
                                            type, getCryptInfo(), this);
    cipher->show();
}

void MainWindow::on_encrypt_clicked()
{
    startCipher(CipherDialog::Type::Encrypt);
}

void MainWindow::on_decrypt_clicked()
{
    startCipher(CipherDialog::Type::Decrypt);
}

CipherDialog::CryptInfo MainWindow::getCryptInfo() const
{
    CipherDialog::CryptInfo info;
    info.inputFile = ui->inputFilePath->text();
    info.outputFile = ui->outputFilePath->text();
    info.password = ui->cryptKey->text();
    return info;
}

void MainWindow::setEnableWorkButtons(bool enable)
{
    ui->encrypt->setEnabled(enable);
    ui->decrypt->setEnabled(enable);
}

void MainWindow::checkReadyToWork()
{
    if( ui->cryptKey->text().isEmpty() ||
        ui->inputFilePath->text().isEmpty() ||
        ui->outputFilePath->text().isEmpty() )
    {
        setEnableWorkButtons(false);
    }
    else
    {
        setEnableWorkButtons(true);
    }
}

void MainWindow::on_cryptKey_textChanged(const QString &text)
{
    checkReadyToWork();
}

void MainWindow::on_inputFilePath_textChanged(const QString &arg1)
{
    checkReadyToWork();
}

void MainWindow::on_outputFilePath_textChanged(const QString &arg1)
{
    checkReadyToWork();
}

void MainWindow::on_openInputFile_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Select file to encrypt/decrypt", QDir::currentPath());
    ui->inputFilePath->setText(path);
}

void MainWindow::on_openOutputFile_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, "Select out file path", QDir::currentPath());
    ui->outputFilePath->setText(path);
}
