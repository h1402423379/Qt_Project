#include "widget.h"
#include"login.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "my_First_demo2_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    login *l=new login();
   l->show();
    Widget w;
//    w.show();
//    if(l->exec()==QDialog::Accepted)
//    {
//        qDebug()<<"Accepted";
//        w.show();
//   }
    return a.exec();
}
