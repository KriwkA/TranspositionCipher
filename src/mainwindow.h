#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include  "cipherdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

private slots:
    void on_encrypt_clicked();
    void on_decrypt_clicked();
    void on_cryptKey_textChanged(const QString& text);
    void on_inputFilePath_textChanged(const QString &arg1);
    void on_outputFilePath_textChanged(const QString &arg1);
    void on_openInputFile_clicked();
    void on_openOutputFile_clicked();

    void on_showPassword_clicked(bool checked);

private:
    void setEnableWorkButtons(bool enable);
    void checkReadyToWork();

    void startCipher(CipherDialog::Type type);
    CipherDialog::CryptInfo getCryptInfo() const;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
