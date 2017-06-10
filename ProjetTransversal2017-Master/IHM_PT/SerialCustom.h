#ifndef SERIALCUSTOM_H
#define SERIALCUSTOM_H

#include <QTextEdit>
#include <QtSerialPort/QtSerialPort>
using namespace std;

class SerialCustom : public QObject
{
    Q_OBJECT


public:
    QSerialPort serialPort;

    QByteArray readData;
    SerialCustom();
    void Analyse_Buffer(void);
    void write(char* seq);
    QTextEdit Console_Lecture;
 public slots:
    void read();
 signals:
    void Fin_analyse();
};

#endif // SERIALCUSTOM_H
