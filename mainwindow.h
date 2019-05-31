#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QMessageBox>
#include <QSerialPortInfo>      //2019.05.31 추가

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    QSerialPort *port;
    QString temp;
    ~MainWindow();

private slots:
    void text_Reading();        //rx로 들어오는 데이터처리용 ISR.

    void on_pushButton_send_clicked();

    void on_pushButton_scan_clicked();

    void on_pushButton_connect_clicked();

    void on_pushButton_disconnect_clicked();

    void on_pushButton_clear_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
