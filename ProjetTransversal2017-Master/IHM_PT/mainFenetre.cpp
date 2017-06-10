#include "mainFenetre.h"


mainFenetre::mainFenetre() : QWidget()
{

    setGeometry(200, 200,400,400);

    //affichage graphe
    //setMouseTracking(true);
    // add two new graphs and set their look:
    Rafraichissement=true;
    QGridLayout *layout = new QGridLayout;
    setLayout(layout);
    connect(&MySerial, SIGNAL(Fin_analyse()), this, SLOT(Replot()));
    QPixmap pixmapFA("FlechesAvant.jpg");
    QIcon ButtonIconFA(pixmapFA);
    QPixmap pixmapFR("FlechesArriere.jpg");
    QIcon ButtonIconFR(pixmapFR);
    QPixmap pixmapFG("FlechesGauche.jpg");
    QIcon ButtonIconFG(pixmapFG);
    QPixmap pixmapFD("FlechesDroite.jpg");
    QIcon ButtonIconFD(pixmapFD);
    QPixmap pixmapTD("FlecheTourelleDroite.jpg");
    QIcon ButtonIconTD(pixmapTD);
    QPixmap pixmapTG("FlecheTourelleGauche.jpg");
    QIcon ButtonIconTG(pixmapTG);
    Avance= new QPushButton("Avancer", this);
    Recule= new QPushButton("Reculer", this);
    TourneADroite= new QPushButton("TournerADroite", this);
    TourneAGauche= new QPushButton("TournerAGauche", this);
    DebutEpreuve= new QPushButton("Debut d'épreuve", this);
    ArretUrgence= new QPushButton("Arret d'urgence", this);
    Deplacement= new QPushButton("Déplacement G",this);

    X_Dest = new QSpinBox;
    Y_Dest = new QSpinBox;
    A_Dest = new QSpinBox;
Console =new QTextEdit;

    Stop= new QPushButton("STOP", this);
    Tourelle= new QDial();
    Avance->setIcon(ButtonIconFA);
    Recule->setIcon(ButtonIconFR);
    TourneADroite->setIcon(ButtonIconFG);
    TourneAGauche->setIcon(ButtonIconFD);
    ArretUrgence->setStyleSheet("background-color: red; border-style: outset; border-width: 2px; border-radius: 10px;border-color: beige;font: bold 14px;min-width: 10em;padding: 6px;");
    Stop->setStyleSheet("background-color: green;");
    connect(Avance, SIGNAL (released()), this, SLOT (Serial_Avance()));
    connect(Recule, SIGNAL (released()), this, SLOT (Serial_Recule()));
    connect(TourneAGauche, SIGNAL (released()), this, SLOT (Serial_TourneGauche()));
    connect(TourneADroite, SIGNAL (released()), this, SLOT (Serial_TourneDroite()));
    connect(Stop, SIGNAL (released()), this, SLOT (Serial_Stop()));
    connect(ArretUrgence, SIGNAL (released()), this, SLOT (Serial_ArretUrgence()));
    connect(DebutEpreuve, SIGNAL (released()), this, SLOT (Serial_DebutEpreuve()));
    connect(Deplacement, SIGNAL (released()), this, SLOT (Serial_DeplacementG()));

    Speed =new QSlider(Qt::Horizontal);

    Speed->setValue(40);
    Speed->setRange(5,100);
    Speed->setFocus();
    Speed->setFixedSize(100,10);
    Speed->setWindowTitle("Speed");
    QLabel *label = new QLabel(this);
    label->setText("\nVitesse");
    QLabel *label2 = new QLabel(this);
    label2->setText("\n\nX");
    QLabel *label3 = new QLabel(this);
    label3->setText("\n\nY");
    QLabel *label4 = new QLabel(this);
    label4->setText("\n\nA");
    Tourelle->setNotchesVisible(true);
    Tourelle->setRange(-90,90);
    Tourelle->wrapping();
    LCD 			= new QLCDNumber();
    LCD->setFixedSize(100,50);
Console->setReadOnly(true);
connect(Tourelle,SIGNAL(sliderReleased()),this,SLOT(Tourelle_Release()));
    connect(Tourelle,SIGNAL(sliderMoved(int)),this,SLOT(Tourelle_Modification(int)));
    Commande_Perso=new QLineEdit (this);
    Commande_Perso->setPlaceholderText("Commande");
    connect(Commande_Perso,SIGNAL(returnPressed()),this, SLOT(Analyse_Commande_Perso()));
    X_Dest->setRange(-99, 99);
    Y_Dest->setRange(-99, 99);
    A_Dest->setRange(-180, 180);
    layout->addWidget(TourneADroite,2,3);
    layout->addWidget(TourneAGauche,2,1);
    layout->addWidget(Avance,1,2);
    layout->addWidget(Recule,3,2);
    layout->addWidget(label,2,2);
    layout->addWidget(Speed,2,2);
    layout->addWidget(LCD,1,4);
    layout->addWidget(Tourelle,2,4);

    layout->addWidget(Stop,3,1);
    layout->addWidget(ArretUrgence,3,3);
    layout->addWidget(DebutEpreuve,1,5,1,3);
    layout->addWidget(label2,2,5);
    layout->addWidget(X_Dest,2,5);
    layout->addWidget(label3,2,6);
    layout->addWidget(Y_Dest,2,6);

    layout->addWidget(label4,2,7);
    layout->addWidget(A_Dest,2,7);
    layout->addWidget(Deplacement,3,5,1,3);
    layout->addWidget(&MySerial.Console_Lecture,5,1,3,7);
    layout->addWidget(Commande_Perso,9,1,1,7);


}

void mainFenetre::Replot()
{

}

void mainFenetre::Chgmt_refresh()
{

}
void mainFenetre::Serial_TourneDroite()
{

    char Text[40]="RD";
    sprintf(Text,"%s %d\r\n",Text, Speed->value());
    MySerial.write(Text);
}

void mainFenetre::Serial_TourneGauche()
{
    char Text[40]="RG";
    sprintf(Text,"%s %d\r\n",Text, Speed->value());
    MySerial.write(Text);
}
void mainFenetre::Serial_Recule()
{
    char Text[40]="B";
    sprintf(Text,"%s %d\r\n",Text, Speed->value());
    MySerial.write(Text);
}
void mainFenetre::Serial_Avance()
{
    char Text[40]="A";
    sprintf(Text,"%s %d\r\n",Text, Speed->value());
    MySerial.write(Text);

}
void mainFenetre::Tourelle_Modification(int value)
{

    LCD->display(value);
}
void mainFenetre::Tourelle_Release()
{

    char Text[40]="CS H A:";
    sprintf(Text,"%s%d\r\n",Text, Tourelle->value());
    MySerial.write(Text);
}

void mainFenetre::Serial_DeplacementG()
{
    char Text[40]="G";
    sprintf(Text,"%s X:%d Y:%d A:%d\r\n",Text, X_Dest->value(),Y_Dest->value(),A_Dest->value());
    MySerial.write(Text);

}
void mainFenetre::Analyse_Commande_Perso()
{
    QString Text=Commande_Perso->text();
    char Text2[100]={};
    sprintf(Text2,"%s\r",Text.toStdString().c_str());
    MySerial.write(Text2);
}


void mainFenetre::keyPressEvent(QKeyEvent *event)
{
    std::cout<<event->key()<<std::endl;

    switch(event->key()){
        case Qt::Key_Up:
            Serial_Avance();
            break;
        case Qt::Key_Left:
        MySerial.write("RG 90 \r\n");

            Serial_TourneGauche();
            break;
        case Qt::Key_Right:
         MySerial.write("RD 90 \r\n");
            break;
        case Qt::Key_Down:
            Serial_Recule();
            break;
        case Qt::Key_Shift :
            Serial_Stop();
            break;
    }
}
