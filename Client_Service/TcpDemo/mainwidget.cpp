#include "mainwidget.h"
#include "ui_mainwidget.h"
#include<QDebug>
#include <QtNetwork>
mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainWidget)
{
    ui->setupUi(this);
    tcpServer = new QTcpServer;
    currentClient = new QTcpSocket;
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address,list){
        if(address.protocol()==QAbstractSocket::IPv4Protocol){
            //我们使用 IPv4地址
            //qDebug()<<address.t oString();
            ui->comboBox_IP->addItem(address.toString());
        }
    }
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(NewConnectionSlot()));
}
void mainWidget::NewConnectuionSlot()
{
    currentClient = tcpServer->nextPendingConnection();
    tcpClient.append(currentClient);
    connect(currentClient,SIGNAL(disconnected()),this,SLOT(disconnectedSlot()));
    connect(currentClient,SIGNAL(readyRead()),this,SLOT(ReadData()));
    //界面显示更新部分
    clientInfo =tr("%1:%2")
            .arg(currentClient->peerAddress().toString().remove("::fffff:"))
            .arg(currentClient->peerPort());
    ui->comboBox_Connection->addItem(clientInfo);
    updateTB_Info(tr("客户端: %1 已联机\n").arg(clientInfo));
}
void mainWidget:: disconnectedSlot()
{
    for(int i=0;i<tcpClient.length();i++){
        if(tcpClient[i]->state()== QAbstractSocket::UnconnectedState){
            qDebug()<<tcpClient[i]->peerAddress().toString();
            clientInfo = tr("%1:%2")
                    .arg(currentClient->peerAddress().toString().remove("::fffff:"))
                    .arg(currentClient->peerPort());
            tcpClient[i]->destroyed();
            tcpClient.removeAt(i);
            // 界面显示更新部分
            ui->comboBox_Connection->removeItem(ui->comboBox_Connection->findText(clientInfo));
            updateTB_Info(tr("客户端: %1 已 脱机\n").arg(clientInfo));
        }
    }
}
void mainWidget::ReadData()
{
    //由于readRead信号并未提供socketDecriptor,所以需要遍历所有客户端
    QByteArray buffer;
    QString IP_Port;
    for(int i=0;i<tcpClient.length();i++){
        buffer = tcpClient[i]->readAll();
        if(buffer.isEmpty()) continue;
        IP_Port = tr("%1:%2")
                .arg(currentClient->peerAddress().toString().remove("::fffff:"))
                .arg(currentClient->peerPort());
        updateTB_Info(tr("[%1:%2]Re:: %3\n")
                      .arg(currentClient->peerAddress().toString().remove("::fffff:"))
                      .arg(currentClient->peerPort())
                      .arg(QString(buffer)));
    }
}
mainWidget::~mainWidget()
{
    delete ui;
}
void mainWidget::updateTB_Info(QString str)
{
    ui->textBrowser_info->moveCursor(QTextCursor::End);
    ui->textBrowser_info->insertPlainText(str);
}
void mainWidget::on_pushButton_connect_clicked()
{
    if(ui->pushButton_connect->text()=="监听"){
        tcpServer->listen(QHostAddress::Any,ui->lineEdit_port->text().toUInt());
        ui->pushButton_connect->setText("断开");
    }
    else
    {
        while(tcpClient.length()!=0)
        {
             tcpClient[0]->disconnectFromHost();
             // tcpClient.removeAt(0);
             ui->pushButton_send->setEnabled(true);
        }
        tcpServer->close();
    }
}
void mainWidget::on_pushButton_send_clicked()
{
    QString command = ui->lineEdit_command->text();
    if(command=="") return;
    QString clientIP=ui->comboBox_Connection->currentText().split(":")[0];
    int clientPort = ui->comboBox_Connection->currentText().split(":")[1].toInt();
    for(int i = 0;i<tcpClient.length();i++)
    {
        if(tcpClient[i]->peerAddress().toString().remove("::ffff:")==clientIP
                &&tcpClient[i]->peerPort()==clientPort){
            tcpClient[i]->write(command.toLatin1());
            updateTB_Info(tr("[1]Send:%2\n")
                          .arg(ui->comboBox_Connection->currentText())
                          .arg(command));
            return;
        }
    }
}

