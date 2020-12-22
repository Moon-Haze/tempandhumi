#ifndef DRAWPLOT_H
#define DRAWPLOT_H

#include <QObject>
#include <QLabel>
#include<QMessageBox>
#include "qcustomplot.h"
#include"DataBase.h"

class DrawPlot : public QObject
{
    Q_OBJECT
public:
    explicit DrawPlot(QCustomPlot *plot,QObject *parent = nullptr);
    void analyzeData(QString StrI1,QString StrI2);//数据读取
    void setLable(QLabel *tlabel,QLabel *hlabel);
signals:
    void analyFinish();
private:
    QCustomPlot *plot;
    QLabel *tLabel;
    QLabel *hLabel;
};

#endif // DRAWPLOT_H
