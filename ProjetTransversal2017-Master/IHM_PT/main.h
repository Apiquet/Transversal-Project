#ifndef MAIN_H
#define MAIN_H
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QtSerialPort/QtSerialPort>
#include "SerialCustom.h"
#include <iostream>
#include <QLabel>
class mainFenetre : public QWidget
{
    Q_OBJECT
public:
    mainFenetre();
    SerialCustom MySerial;

    bool Rafraichissement;

private:
    QPushButton *m_bouton;

};

#endif // MAIN_H
