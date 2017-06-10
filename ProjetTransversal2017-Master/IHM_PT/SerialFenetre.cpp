#include "SerialFenetre.h"


SerialFenetre::SerialFenetre(): QWidget()
{

    setGeometry(200, 200,400,400);
    QSerialPort Serial_Temp;
    Bouton_Validation =new QPushButton("OK",this);
    QGridLayout *layout = new QGridLayout;
    setLayout(layout);
    layout->addWidget(Bouton_Validation,1,1);
      connect(Bouton_Validation, SIGNAL (released()), this, SLOT(Validation_Serial()));
}

