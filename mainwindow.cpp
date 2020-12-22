#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("温湿度监测系统"));  //设置标题
    serial = new SerialPort();
    plot=new DrawPlot(ui->widget_plot);
    plot->setLable(ui->tLabel,ui->hLabel);
    QThread *thread_serial=new QThread(this);
    QThread *thread_plot=new QThread(this);
    serial->moveToThread(thread_serial);
    plot->moveToThread(thread_plot);
    thread_serial->start();
    thread_plot->start();
    connect(this,&MainWindow::searchPosts,serial,&SerialPort::searchPost);
    connect(this,&MainWindow::openSerial,serial,&SerialPort::openSerialPort);
    connect(serial,&SerialPort::openSerial,this,&MainWindow::openPost);
    connect(serial,&SerialPort::searchFinish,this,&MainWindow::finishSearchPost);
    connect(serial,&SerialPort::recieveData,plot,&DrawPlot::analyzeData);
    connect(plot,&DrawPlot::analyFinish,this,&MainWindow::drawPlot);
    ui->btn_search_port->click();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete serial;
    delete plot;
}

void MainWindow::on_btn_open_port_clicked()
{
    if(!serial->isOpen())
    {
        ui->comboBox->setDisabled(true); //禁止修改串口
        ui->statusbar->clearMessage();
        ui->statusbar->showMessage("正在打开串口...");
        emit openSerial(ui->comboBox->currentText());
    }  else {
        ui->comboBox->setEnabled(true);//串口号下拉按钮使能工作
        serial->close();
        ui->statusbar->showMessage("已关闭串口",30000);
        ui->btn_open_port->setText("打开串口");//按钮显示“打开串口”
        ui->btn_search_port->setEnabled(true);
    }
}

void MainWindow::on_btn_search_port_clicked()
{
    ui->comboBox->setEnabled(true);//串口号下拉按钮使能工作
    serial->close();
    ui->statusbar->clearMessage();
    ui->btn_open_port->setText("打开串口");//按钮显示“打开串口”
    ui->statusbar->showMessage("正在搜索串口...");
    emit searchPosts();
}

void MainWindow::openPost(bool is)
{
    if(is){
        ui->btn_open_port->setText("关闭串口");//按钮显示“打开串口”
        ui->btn_search_port->setDisabled(true);
        ui->statusbar->showMessage("成功打开串口",30000);
    }else{
        ui->comboBox->setEnabled(true);
        ui->statusbar->showMessage("打开串口失败",30000);
        QMessageBox::warning(this,"Error","串口打开失败", QMessageBox::Ok);
    }
}

void MainWindow::drawPlot()
{
    ui->widget_plot->replot();
}

void MainWindow::finishSearchPost(QStringList list)
{
    ui->comboBox->clear();
    ui->comboBox->addItems(list);
    ui->statusbar->showMessage("搜索串口已完成",30000);
}
