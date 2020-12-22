#include "serialport.h"

SerialPort::SerialPort(QObject *parent):QObject (parent)
{
    serial=new QSerialPort;
    connect(serial,&QSerialPort::readyRead,this,&SerialPort::readData);
}

void SerialPort::searchPost()
{
    QStringList posts;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())//读取串口信息
    {
        if(!info.isBusy()){
            posts<<info.portName();
        }
    }
    emit searchFinish(posts);
}

void SerialPort::readData()
{
    serial->flush();
    DataPacket packet(serial->readAll());
    qDebug()<<"\t temp="<<packet["temp"].toString()<<"\thumi="<<packet["humi"].toString();
    emit recieveData(packet["temp"].toString(),packet["humi"].toString());
}

void SerialPort::openSerialPort(const QString port)
{
    if(!serial->isOpen()){
        serial->setPortName(port); //设置串口号
        serial->setBaudRate(QSerialPort::Baud115200); //设置波特
        serial->setDataBits(QSerialPort::Data8); //设置数据位数
        serial->setParity(QSerialPort::NoParity);//设置奇偶校验
        serial->setStopBits(QSerialPort::OneStop);//设置停止位
        serial->setFlowControl(QSerialPort::NoFlowControl);//非流控制
        emit openSerial(serial->open(QIODevice::ReadWrite));
    }else{
        emit openSerial(true);
    }
}

void SerialPort::write(QString str)
{
    if(serial->isOpen()){
        serial->write(str.toStdString().data());
        serial->flush();
    }
}

bool SerialPort::isOpen() const
{
    return serial->isOpen();
}

void SerialPort::close()
{
    serial->close();
}

SerialPort::~SerialPort()
{
    delete serial;
}
