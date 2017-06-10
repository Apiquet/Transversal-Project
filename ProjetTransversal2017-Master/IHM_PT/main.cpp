#include <QApplication>
#include <QPushButton>
#include "mainFenetre.h"
#include "SerialFenetre.h"
extern string D;
extern bool Configuration;
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    D="COM8";
    //while(Configuration==false);
mainFenetre Fenetre;
Fenetre.show();


    return app.exec();
}
