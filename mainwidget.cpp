#include "mainwidget.h"
#include "ui_mainwidget.h"

bool storingData(double temp,double humi){
    QSqlQuery sq;
    sq.prepare("INSERT INTO tempandhumi VALUES(DEFAULT,:temp,:humi,NOW())");
    sq.bindValue(":temp",temp);
    sq.bindValue(":humi",humi);
    return sq.exec();
}

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("温湿度监测系统"));  //设置标题
    myserial = new SerialPort();
    setupPlot();//图形界面初始化函数
    connect(myserial,&SerialPort::recieveData,this,&MainWidget::AnalyzeData);
    QThread *thread=new QThread(this);
    myserial->moveToThread(thread);
    thread->start();
    connect(this,&MainWidget::searchPosts,myserial,&SerialPort::searchPost);
    connect(this,&MainWidget::openSerial,myserial,&SerialPort::openSerialPort);
    connect(myserial,&SerialPort::openSerial,[=](bool is){
        if(is){
            ui->btn_open_port->setText("关闭串口");//按钮显示“打开串口”
            ui->btn_search_port->setDisabled(true);
        }else{
            QMessageBox::warning(nullptr,"ERROR","串口打开失败");
            ui->comboBox->setEnabled(true);//串口号下拉按钮使能工作
        }
    });
    connect(myserial,&SerialPort::searchFinish,[=](QStringList posts){
        ui->comboBox->clear();
        ui->comboBox->addItems(posts);
    });
    ui->btn_search_port->click();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_btn_open_port_clicked()
{
    if(!myserial->isOpen())
    {
        ui->comboBox->setDisabled(true); //禁止修改串口
        emit openSerial(ui->comboBox->currentText());
    }  else {
        ui->comboBox->setEnabled(true);//串口号下拉按钮使能工作
        myserial->close();
        ui->btn_open_port->setText("打开串口");//按钮显示“打开串口”
        ui->btn_search_port->setEnabled(true);
    }
}

void MainWidget::AnalyzeData(QString StrI1,QString StrI2)
{
    ui->tLabel->setText(StrI1);//显示读取温度值
    ui->hLabel->setText(StrI2);//显示读取湿度值
    double dataI1=StrI1.toDouble();//将字符串转换成double类型进行数据处理
    double dataI2=StrI2.toDouble();//将字符串转换成double类型进行数据处理
    storingData(dataI1,dataI2);
    mycurrenttime = QDateTime::currentDateTime();//获取系统时间
    double xzb = mystarttime.msecsTo(mycurrenttime)/1000.0;//获取横坐标，相对时间就是从0开始
    ui->widget_plot->graph(0)->addData(xzb,dataI1);//添加数据1到曲线1
    ui->widget_plot->graph(1)->addData(xzb,dataI2);//添加数据1到曲线1
    if(xzb>30)
    {
        ui->widget_plot->xAxis->setRange((double)qRound(xzb-30),xzb);//设定x轴的范围
    } else{
        ui->widget_plot->xAxis->setRange(0,30);//设定x轴的范围
    }
    ui->widget_plot->replot();//每次画完曲线一定要更新显示
}

void MainWidget::setupPlot()
{
    ui->widget_plot->addGraph();//添加一条曲线
    QPen pen;
    pen.setWidth(1);//设置画笔线条宽度
    pen.setColor(Qt::blue);
    ui->widget_plot->graph(0)->setPen(pen);//设置画笔颜色
    ui->widget_plot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); //设置曲线画刷背景
    ui->widget_plot->graph(0)->setName("0-100");
    ui->widget_plot->graph(0)->setAntialiasedFill(false);
    ui->widget_plot->graph(0)->setLineStyle((QCPGraph::LineStyle)1);//曲线画笔
    ui->widget_plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone,5));//曲线形状

    ui->widget_plot->addGraph();//添加一条曲线
    pen.setColor(Qt::red);
    ui->widget_plot->graph(1)->setPen(pen);//设置画笔颜色
    ui->widget_plot->graph(1)->setBrush(QBrush(QColor(0, 0, 255, 20))); //设置曲线画刷背景
    ui->widget_plot->graph(1)->setName("0-100");
    ui->widget_plot->graph(1)->setAntialiasedFill(false);
    ui->widget_plot->graph(1)->setLineStyle((QCPGraph::LineStyle)1);//曲线画笔
    ui->widget_plot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone,5));//曲线形状
    //设置图表
    ui->widget_plot->xAxis->setLabel(QStringLiteral("时间/s"));//设置x坐标轴名称
    ui->widget_plot->xAxis->setLabelColor(QColor(20,20,20));//设置x坐标轴名称颜色
    ui->widget_plot->xAxis->setRange(0,30);//设定x轴的范围
    ui->widget_plot->yAxis->setLabel(QStringLiteral("PH & TDS"));//设置y坐标轴名称
    ui->widget_plot->yAxis->setLabelColor(QColor(20,20,20));//设置y坐标轴名称颜色
    ui->widget_plot->yAxis->setRange(0,100);//设定y轴范围

    ui->widget_plot->axisRect()->setupFullAxesBox(true);//设置缩放，拖拽，设置图表的分类图标显示位置
    ui->widget_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom| QCP::iSelectAxes);
    ui->widget_plot->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop | Qt::AlignRight);//图例显示位置右上
    ui->widget_plot->legend->setVisible(true);//显示图例
    ui->widget_plot->replot();
}


void MainWidget::on_btn_search_port_clicked()
{
    ui->comboBox->setEnabled(true);//串口号下拉按钮使能工作
    myserial->close();
    ui->btn_open_port->setText("打开串口");//按钮显示“打开串口”
    emit searchPosts();
}
