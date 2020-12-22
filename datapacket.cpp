#include "datapacket.h"

DataPacket::DataPacket(const QString &str)
{
    int in,len;
    for(auto item:str.split(QRegExp("&"), Qt::SkipEmptyParts)){
        in=item.indexOf('=');
        len=item.size()-in;
        maps.insert(item.replace(in,len,""),item.mid(in+1,len));
    }
}

Data DataPacket::at(const QString &num)
{
    return Data(maps[num]);
}

Data DataPacket::operator[](const QString &num)
{
    return at(num);
}

QList<QString> DataPacket::keys() const
{
    return maps.keys();
}
