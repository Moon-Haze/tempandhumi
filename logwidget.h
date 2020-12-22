#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QStackedWidget>
#include<QString>
#include<QMessageBox>
#include<QDebug>
#include<QSqlDatabase>
#include<QSqlError>
#include<QSqlQuery>
#include<QSettings>
#include"mainpageproxy.h"
#include"DataBase.h"

namespace Ui {
class LogWidget;
}

class LogWidget : public QStackedWidget
{
    Q_OBJECT

public:
    explicit LogWidget(QWidget *parent = nullptr);
    void setMainPage(MainPageProxy* mpp);
    ~LogWidget();

private slots:
    void on_SignUpButton_clicked();

    void on_backButton_clicked();;

    void on_logInButton_clicked();

    void on_logInIdlineEdit_returnPressed();

    void on_logUpIdlineEdit_returnPressed();

    void on_logUpPwlineEdit_returnPressed();

    void on_logUpRpwlineEdit_returnPressed();

    void on_logUpButton_clicked();

    void on_logInPwlineEdit_returnPressed();

    void on_pWcheckBox_stateChanged(int arg1);
protected:
    //    void closeEvent(QCloseEvent* event);

private:
    Ui::LogWidget *ui;
    MainPageProxy* mw;
    bool SQL_INIT;
    QSqlDatabase db;
};

#endif // LOGWIDGET_H
