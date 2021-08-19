
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QString>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton *btn = new QPushButton(this);
    btn->setText("myButton");
    btn->setGeometry(120,400,180,50);
//1.F4 F3 ui界面编辑方式.ui下操作
//2.ui界面 signal slot Edit 方式.ui下操作
//3.自动关联方式,button点右键 转到槽.ui下操作
//4.最常规的用法,QT4下使用,现在不推荐
    //connect(btn,SIGNAL(Clicked()),this,SLOT(myclicked()));
   // connect(ui->lineEdit,SIGNAL(textEdited(QString)),ui->textEdit,SLOT(setText(QString)));
//5.connect()函数基于函数指针的重载形式，qt5下使用，推荐：
    //Qt4下的对比用法   connect(btn,SIGNAL(clicked()),this,SLOT(myclicked()));
                     // connect(btn,&QPushButton::clicked,this,&MainWindow::myclicked);
//6.手动提交，emit方式
//QT4
  connect(this,SIGNAL(mySignal()),this,SLOT(myclicked()));
//Qt5
       //connect(btn,&QPushButton::clicked,this,&MainWindow::myclicked);
//7.lambda, c++11下使用
  connect(btn,&QPushButton::clicked,
          [btn](){
      if(btn->text()=="lambda")
          btn->setText("QSt");
      else
          btn->setText("lambda");
      qDebug()<<"1111111111";
  });

//A.一个SINGAL触发俩个SLOT，另一个在ui界面中实现。俩个SLOT的先后顺序并不能确定
  connect(ui->lineEdit,SIGNAL(textEdited(QString)),ui->textEdit,SLOT(setText(QString)));

//B.一个SLOT可以被多个SINGAL触发
    //三个俺就的信号都关联到 FoodIsComing槽函数
    connect(ui->pushButton_Z,SIGNAL(clicked()),this,SLOT(FoodIsComing()));
    connect(ui->pushButton_L,SIGNAL(clicked()),this,SLOT(FoodIsComing()));
    connect(ui->pushButton_H,SIGNAL(clicked()),this,SLOT(FoodIsComing()));
}
void MainWindow::myclicked()
{
    qDebug()<<"myclicked";
   ui->lineEdit_2->setText("Qt5我要变变变");

}

void MainWindow::on_pushButton_2_clicked()
{
    //1.改变text
    ui->pushButton_2->setText("hello");
    //2.手动提交
    emit mySignal();
}
void MainWindow::FoodIsComing()
{
    //获取信号源头对象的名称
    QString strObjectSrc = this->sender()->objectName();
    qDebug()<<strObjectSrc;//打印源头对象名称
    //将要显示的消息
    QString strMsg;
    //判断是哪个按钮发的信号
    if("pushButton_Z"==strObjectSrc)
    {
        strMsg = tr("Hello 张吃货！ Your food is coming");
    }
    else if("pushButton_L"==strObjectSrc)
    {
        strMsg = tr("Hello 李吃货！ Your food is coming");
    }
    else if("pushButton_H"==strObjectSrc)
    {
        strMsg = tr("Hello 胡吃货！ Your food is coming");
    }
    else{
        return;
    }
    //显示送餐消息
    QMessageBox::information(this,tr("Food"),strMsg);
}
MainWindow::~MainWindow()
{
    delete ui;
}

