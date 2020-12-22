#ifndef DATAPACKET_H
#define DATAPACKET_H
#include <QObject>
#include<QMap>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<QString>
#include"data.h"

class DataPacket
{
public:
    DataPacket(const QString& str="");
    Data at(const QString& num);
    Data operator[](const QString& num);
    QList<QString> keys() const;
private:
    QMap<QString,QString> maps;
};

#endif // DATAPACKET_H
