#ifndef WIDGET_H
#define WIDGET_H
#include <QDebug>//用于在控制台输出调试信息
#include <QTime>//定时器
#include <QPainter>//坐标系绘图
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include <QWidget>
#include<QEvent>
#include<QShowEvent>
#include<QThread>
#include <QMetaType>
#include"serialport.h"
#include<QString>

namespace Ui {
class Widget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    void setupPlot();//初始化
private slots:
    void on_btn_open_port_clicked();
    void on_btn_search_port_clicked();
public slots:
    void AnalyzeData(QString StrI1,QString StrI2);//数据读取
signals:
    void searchPosts();
    void openSerial(const QString& port);
private:
    Ui::Widget *ui;
    SerialPort *myserial;//声明串口类，myserial是QSerialPort的实例
    QByteArray alldata;//接收串口数据
    //绘图函数
    QDateTime mycurrenttime;//系统当前时间
    QDateTime mystarttime;//系统开始时间

};

#endif // WIDGET_H
