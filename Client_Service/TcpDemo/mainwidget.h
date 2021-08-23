#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QtNetwork>
QT_BEGIN_NAMESPACE
namespace Ui { class mainWidget; }
QT_END_NAMESPACE

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    mainWidget(QWidget *parent = nullptr);
    ~mainWidget();
public slots:
    void NewConnectuionSlot();
    void disconnectedSlot();
    void ReadData();
    void on_pushButton_connect_clicked();
    void on_pushButton_send_clicked();
    void updateTB_Info(QString);
private:
    Ui::mainWidget *ui;

    QTcpServer *tcpServer;
    QList<QTcpSocket *> tcpClient;
    QTcpSocket *currentClient;
    QString clientInfo;
};
#endif // MAINWIDGET_H
