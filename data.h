#ifndef DATA_H
#define DATA_H

#include <QObject>
#include<QString>
#include<QStringList>
#include<QList>
class Data
{
private:
    QString data;

public:
    Data(const QString& str="");
QString toString();
    int toInt();
    float toFloat();
    double toDouble();
    long toLong();
    QList<int> toIntList();
    QList<float> toFloatList();
    QList<double> toDoubleList();
    QStringList toStringList();
};

#endif // DATA_H
