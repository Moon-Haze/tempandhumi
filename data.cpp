#include "data.h"

Data::Data(const QString &str):data(str)
{
}

QString Data::toString()
{
    return data;
}

int Data::toInt()
{
    return data.toInt();
}

float Data::toFloat()
{
    return data.toFloat();
}

double Data::toDouble()
{
    return data.toDouble();
}

long Data::toLong()
{
    return data.toLong();
}

QList<int> Data::toIntList()
{
    QStringList list=data.split(",",Qt::SkipEmptyParts);
    QList<int> itemList;
    for(auto item:list){
        itemList.append(item.toInt());
    }
    return itemList;
}

QList<float> Data::toFloatList()
{
    QStringList list=data.split(",",Qt::SkipEmptyParts);
    QList<float> itemList;
    for(auto item:list){
        itemList.append(item.toFloat());
    }
    return itemList;
}

QList<double> Data::toDoubleList()
{
    QStringList list=data.split(",",Qt::SkipEmptyParts);
    QList<double> itemList;
    for(auto item:list){
        itemList.append(item.toDouble());
    }
    return itemList;
}

QStringList Data::toStringList()
{
    return data.split(",",Qt::SkipEmptyParts);
}
