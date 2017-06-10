#ifndef MAINFENETRE_H
#define MAINFENETRE_H
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QtSerialPort/QtSerialPort>
#include "SerialCustom.h"
#include <iostream>
#include <QLabel>
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QGridLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <vector>
#include <QSlider>
#include <QGraphicsScene>
#include <QDial>
#include <QLCDNumber>
#include <QSpinBox>
#include <Qstring>
#include <QtGui/QKeyEvent>

class mainFenetre : public QWidget
{
    Q_OBJECT
public:
    mainFenetre();
    SerialCustom MySerial;
    QCheckBox *Refresh;

    bool Rafraichissement;

private:
    QPushButton *Avance;
    QPushButton *Recule;
    QPushButton *TourneADroite;
    QPushButton *TourneAGauche;
    QPushButton *DebutEpreuve;
    QPushButton *Deplacement;
    QPushButton *ArretUrgence;

    QPushButton *Stop;
    QDial *Tourelle;
    QLineEdit  *Commande_Perso;

    QSpinBox *X_Dest;
    QSpinBox *Y_Dest;
    QSpinBox *A_Dest;
    QSlider *Speed;
    QLCDNumber *LCD;
    QTextEdit *Console;
    QByteArray Cache;//on copie la chaine
signals:
protected:
    void keyPressEvent(QKeyEvent *event);


public slots:
    void Chgmt_refresh();
    void Replot();
    void Serial_TourneDroite();
    void Serial_TourneGauche();
    void Serial_Recule();
    void Serial_Avance();
    void Serial_Stop(){MySerial.write("S\r\n"); }
    void Serial_ArretUrgence(){MySerial.write("Q\r\n");}
    void Tourelle_Modification(int value);
    void Serial_DebutEpreuve(){MySerial.write("D\r\n");}
    void Serial_DeplacementG();
void Tourelle_Release();
void Analyse_Commande_Perso();

};

#endif // MAINFENETRE_H


