#include "SerialCustom.h"
#include "define.h"
#include "iostream"
SerialCustom::SerialCustom()
{
    QTextStream standardOutput(stdout);
    cout<<"111"<<endl;
    /*Paramétrage Port Serie*/
    QString serialPortName = QString::fromStdString(D);
    serialPort.setPortName(serialPortName);
    connect(&serialPort, SIGNAL(readyRead()), this, SLOT(read()));//connexion de l'interruption sur reception de donnees

    int serialPortBaudRate =  QSerialPort::BAUDRATE;
    serialPort.setBaudRate(serialPortBaudRate);
    if (!serialPort.open(QIODevice::ReadWrite )) {
        standardOutput << QObject::tr("Failed to open port %1, error: %2").arg(serialPortName).arg(serialPort.errorString()) << endl;
        //abort();
        return ;
    }
    serialPort.setDataTerminalReady(true);
Console_Lecture.setReadOnly(true);
    this->write("\n\n\r\n");
}

void SerialCustom::write(char *seq)
{
    QTextStream standardOutput(stdout);
    serialPort.write(seq);
    serialPort.waitForBytesWritten(5000);
    return;
}
void SerialCustom::read()
{
        static QString Stockage;
        Stockage.append(serialPort.readAll());


        Console_Lecture.setText(Stockage);


    return ;
}

