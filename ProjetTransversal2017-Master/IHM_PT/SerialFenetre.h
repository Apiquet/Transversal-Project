#ifndef SERIALFENETRE_H
#define SERIALFENETRE_H

#include <QObject>
#include <mainFenetre.h>
extern bool Configuration;
class SerialFenetre  : public QWidget
{
public:
    SerialFenetre();
private:
    QPushButton *Bouton_Validation;

public slots:
    void Validation_Serial()
    {
        Configuration=true;
    }

};

#endif // SERIALFENETRE_H
