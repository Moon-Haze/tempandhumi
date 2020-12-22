#include "logwidget.h"
#include"mainpageproxy.h"
#include <QApplication>
#include<QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogWidget* w=new LogWidget();
    MainPageProxy* mw=new MainPageProxy();
    w->setMainPage(mw);
    w->show();
    return a.exec();
}
