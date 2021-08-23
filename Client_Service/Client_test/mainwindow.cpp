#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtNetwork>
#include<QPlainTextEdit>
QTcpSocket *tcpClient;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //初始化TCP客户端
    tcpClient = new  QTcpSocket(this);
    tcpClient->abort();
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(ReadData()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString localHostName = QHostInfo::localHostName();
    ui->lineEditLocalHostName->setText(localHostName);
    QHostInfo hostInfo = QHostInfo::fromName(localHostName);
    QList<QHostAddress> listAddress = hostInfo.addresses();
    if(!listAddress.isEmpty())
    {
        ui->textEditAddress->clear();
        ui->textEditAddress->setPlainText(listAddress.at(2).toString());

    }
}
void MainWindow::on_pushButton_3_clicked()
{

}
void MainWindow::on_btnConnect_clicked()
{
    tcpClient->connectToHost(ui->edtIP->text(),ui->edtPort->text().toInt());
    if(tcpClient->waitForConnected(1000))
    {
        ui->btnConnect->setText("断开");
        ui->btnSend->setEnabled(true);
        qDebug()<<"connected:";
    }
}
void MainWindow::ReadData()
{
    QByteArray buffer = tcpClient->readAll();
    if(!buffer.isEmpty())
    {
        ui->edtRecv->append(buffer);
    }
}
void MainWindow::on_btnSend_clicked()
{
    QString data = ui->edtSend->toPlainText();
    if(data!="")
    {
        tcpClient->write(data.toLatin1());//qt5出去了,tolatin1
    }
}
