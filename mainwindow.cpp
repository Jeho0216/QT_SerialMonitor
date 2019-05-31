#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //----- ADD JHLEE 2019.05.24-------
    port = new QSerialPort();
    on_pushButton_scan_clicked();
    QObject::connect(port, SIGNAL(readyRead()), this, SLOT(text_Reading()));
}

void MainWindow::text_Reading()
{
    QByteArray read_data;

    read_data = port->readAll();
    temp += QString(read_data);     //QString 변수에 읽은 문자열을 이어붙힘.
    qDebug() << temp;

    if(strchr(read_data.data(), '\n')){     //읽어온 문자열(read_data)에 '\n'문자 존재하면
        ui->textEdit->append(temp);     //출력
        ui->textEdit->show();
        temp = "";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_send_clicked()
{
    QByteArray send_data;
    while(1){
        send_data.append(ui->lineEdit->text().toUtf8().left(10));      //utf-8로 변환 후, 왼쪽의 1byte 읽기.
            break;
    }
    send_data.append('\n');
    port->write(send_data.data());
    qDebug() << send_data.data();
    ui->lineEdit->clear();
}

void MainWindow::on_pushButton_scan_clicked()
{
    ui->comboBox_port->clear();
    foreach(const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
        ui->comboBox_port->addItem(serial_port_info.portName());
    }
}

void MainWindow::on_pushButton_connect_clicked()
{
#if 1
    port->setPortName("/dev/" + ui->comboBox_port->currentText());
#else
    port->setPortName("/dev/ttyUSB0");
#endif
    port->setBaudRate(QSerialPort::Baud115200);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);

    if(!port->open(QIODevice::ReadWrite)){      //여기서 port open 수행. 반대로 close()
        qDebug() << "\n Serial Port Open Error " << ui->comboBox_port->currentText() << endl;
        exit(1);
    }
    else{
        qDebug() << "\n Serial Port Open Success --> " << ui->comboBox_port->currentText() << endl;
        ui->pushButton_connect->setDisabled(1);
        ui->pushButton_disconnect->setDisabled(0);
    }
}

void MainWindow::on_pushButton_disconnect_clicked()
{
    port->close();
    qDebug() << "\nClose port" << endl;
    ui->pushButton_connect->setDisabled(0);
    ui->pushButton_disconnect->setDisabled(1);
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->textEdit->clear();
}
