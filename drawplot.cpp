#include "drawplot.h"


bool storingData(double temp,double humi){
    QSqlQuery sq;
    sq.prepare("INSERT INTO tempandhumi VALUES(DEFAULT,:temp,:humi,NOW())");
    sq.bindValue(":temp",temp);
    sq.bindValue(":humi",humi);
    return sq.exec();
}

DrawPlot::DrawPlot(QCustomPlot *plot,QObject *parent) : QObject(parent)
{
    this->plot=plot;
    plot->addGraph();//添加一条曲线
    QPen pen;
    pen.setWidth(1);//设置画笔线条宽度
    pen.setColor(Qt::blue);
    plot->graph(0)->setPen(pen);//设置画笔颜色
    plot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); //设置曲线画刷背景
    plot->graph(0)->setName("温度");
    plot->graph(0)->setAntialiasedFill(false);
    plot->graph(0)->setLineStyle((QCPGraph::LineStyle)1);//曲线画笔
    plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone,5));//曲线形状

    plot->addGraph();//添加一条曲线
    pen.setColor(Qt::red);
    plot->graph(1)->setPen(pen);//设置画笔颜色
    plot->graph(1)->setBrush(QBrush(QColor(0, 0, 255, 20))); //设置曲线画刷背景
    plot->graph(1)->setName("湿度");
    plot->graph(1)->setAntialiasedFill(false);
    plot->graph(1)->setLineStyle((QCPGraph::LineStyle)1);//曲线画笔
    plot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone,5));//曲线形状
    //设置图表
    plot->xAxis->setLabel(QStringLiteral("时间/s"));//设置x坐标轴名称
    plot->xAxis->setLabelColor(QColor(20,20,20));//设置x坐标轴名称颜色
    plot->xAxis->setRange(0,30);//设定x轴的范围
    plot->yAxis->setLabel(QStringLiteral("PH & TDS"));//设置y坐标轴名称
    plot->yAxis->setLabelColor(QColor(20,20,20));//设置y坐标轴名称颜色
    plot->yAxis->setRange(0,100);//设定y轴范围

    plot->axisRect()->setupFullAxesBox(true);//设置缩放，拖拽，设置图表的分类图标显示位置
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom| QCP::iSelectAxes);
    plot->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop | Qt::AlignRight);//图例显示位置右上
    plot->legend->setVisible(true);//显示图例
    plot->replot();
}

void DrawPlot::analyzeData(QString StrI1, QString StrI2)
{
    static bool SQL_INIT=false;
    if(!SQL_INIT){
        SQL_INIT=true;
        sqlInit();
    }
    tLabel->setText(StrI1);//显示读取温度值
    hLabel->setText(StrI2);//显示读取湿度值
    double dataI1=StrI1.toDouble();//将字符串转换成double类型进行数据处理
    double dataI2=StrI2.toDouble();//将字符串转换成double类型进行数据处理
    storingData(dataI1,dataI2);
    static QDateTime starttime=QDateTime::currentDateTime();
    QDateTime currenttime = QDateTime::currentDateTime();//获取系统时间
    double xzb = starttime.msecsTo(currenttime)/1000.0;//获取横坐标，相对时间就是从0开始
    plot->graph(0)->addData(xzb,dataI1);//添加数据1到曲线1
    plot->graph(1)->addData(xzb,dataI2);//添加数据1到曲线1
    if(!plot->xAxis->range().contains(xzb)) {
        plot->xAxis->setRange(xzb,xzb+30);//设定x轴的范围
    }
//    plot->replot();
    emit analyFinish();
}

void DrawPlot::setLable(QLabel *tlabel, QLabel *hlabel)
{
    this->tLabel=tlabel;
    this->hLabel=hlabel;
}
