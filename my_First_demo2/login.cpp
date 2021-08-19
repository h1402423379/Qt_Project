#include "login.h"
#include "ui_login.h"
#include<QString>
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

}

login::~login()
{
    delete ui;
}
void login::on_pushButton_clicked()
{
    QString str1,str2,str3,str4;
    str3 = "hou";
    str4 = "123";
    str1=ui->lineEdit->text();
    str2=ui->lineEdit_2->text();
    if(QString::compare(str1,str3)==0)
    {
        if(QString::compare(str2,str4)==0)
        {
            ui->lineEdit_3->setText("密码正确");
        }
        else{
            ui->lineEdit_3->setText("密码错误");
        }

    }
    else{
        ui->lineEdit_3->setText("密码或用户名错误");
    }

}
