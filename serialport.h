#ifndef SERIALPORT_H
#define SERIALPORT_H
#include <QtSerialPort/QSerialPort>//串口
#include <QtSerialPort/QSerialPortInfo>//串口
#include <QStringList>
#include<QString>
#include<QDebug>
#include"datapacket.h"

class SerialPort: public QObject
{
    Q_OBJECT
private:
    QSerialPort *serial;
signals:
    void recieveData(QString StrI1,QString StrI2);
    void searchFinish(QStringList post);
    void openSerial(bool is_open);
public slots:
    void searchPost();
    void openSerialPort(const QString port);
public:
   explicit SerialPort (QObject *parent = nullptr);
    void readData();//数据读取
    void write(QString str);
    bool isOpen() const;
    void close();
    ~SerialPort();
};

#endif // SERIALPORT_H
