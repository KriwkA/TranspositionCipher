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
    ~MainWindow();

private slots:
    void on_encrypt_clicked();
    void on_decrypt_clicked();
    void on_cryptKey_textChanged(const QString &arg1);

private:

    CipherDialog::CryptInfo getCryptInfo() const;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H