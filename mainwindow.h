#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>//用于在控制台输出调试信息
#include <QTime>//定时器
#include <QPainter>//坐标系绘图
#include <QWidget>
#include<QEvent>
#include<QShowEvent>
#include<QThread>
#include <QMetaType>
#include"serialport.h"
#include"drawplot.h"
#include<QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_btn_open_port_clicked();
    void on_btn_search_port_clicked();
    void openPost(bool is);
    void drawPlot();
    void finishSearchPost(QStringList list);
public slots:
signals:
    void searchPosts();
    void openSerial(const QString& port);
private:
    Ui::MainWindow *ui;
    SerialPort *serial;//声明串口类
    DrawPlot* plot;
};

#endif // MAINWINDOW_H
