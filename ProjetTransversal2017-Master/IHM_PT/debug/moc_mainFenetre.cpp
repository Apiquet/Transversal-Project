/****************************************************************************
** Meta object code from reading C++ file 'mainFenetre.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainFenetre.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainFenetre.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mainFenetre_t {
    QByteArrayData data[16];
    char stringdata0[242];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mainFenetre_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mainFenetre_t qt_meta_stringdata_mainFenetre = {
    {
QT_MOC_LITERAL(0, 0, 11), // "mainFenetre"
QT_MOC_LITERAL(1, 12, 13), // "Chgmt_refresh"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 6), // "Replot"
QT_MOC_LITERAL(4, 34, 19), // "Serial_TourneDroite"
QT_MOC_LITERAL(5, 54, 19), // "Serial_TourneGauche"
QT_MOC_LITERAL(6, 74, 13), // "Serial_Recule"
QT_MOC_LITERAL(7, 88, 13), // "Serial_Avance"
QT_MOC_LITERAL(8, 102, 11), // "Serial_Stop"
QT_MOC_LITERAL(9, 114, 19), // "Serial_ArretUrgence"
QT_MOC_LITERAL(10, 134, 21), // "Tourelle_Modification"
QT_MOC_LITERAL(11, 156, 5), // "value"
QT_MOC_LITERAL(12, 162, 19), // "Serial_DebutEpreuve"
QT_MOC_LITERAL(13, 182, 19), // "Serial_DeplacementG"
QT_MOC_LITERAL(14, 202, 16), // "Tourelle_Release"
QT_MOC_LITERAL(15, 219, 22) // "Analyse_Commande_Perso"

    },
    "mainFenetre\0Chgmt_refresh\0\0Replot\0"
    "Serial_TourneDroite\0Serial_TourneGauche\0"
    "Serial_Recule\0Serial_Avance\0Serial_Stop\0"
    "Serial_ArretUrgence\0Tourelle_Modification\0"
    "value\0Serial_DebutEpreuve\0Serial_DeplacementG\0"
    "Tourelle_Release\0Analyse_Commande_Perso"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mainFenetre[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x0a /* Public */,
       3,    0,   80,    2, 0x0a /* Public */,
       4,    0,   81,    2, 0x0a /* Public */,
       5,    0,   82,    2, 0x0a /* Public */,
       6,    0,   83,    2, 0x0a /* Public */,
       7,    0,   84,    2, 0x0a /* Public */,
       8,    0,   85,    2, 0x0a /* Public */,
       9,    0,   86,    2, 0x0a /* Public */,
      10,    1,   87,    2, 0x0a /* Public */,
      12,    0,   90,    2, 0x0a /* Public */,
      13,    0,   91,    2, 0x0a /* Public */,
      14,    0,   92,    2, 0x0a /* Public */,
      15,    0,   93,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void mainFenetre::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        mainFenetre *_t = static_cast<mainFenetre *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Chgmt_refresh(); break;
        case 1: _t->Replot(); break;
        case 2: _t->Serial_TourneDroite(); break;
        case 3: _t->Serial_TourneGauche(); break;
        case 4: _t->Serial_Recule(); break;
        case 5: _t->Serial_Avance(); break;
        case 6: _t->Serial_Stop(); break;
        case 7: _t->Serial_ArretUrgence(); break;
        case 8: _t->Tourelle_Modification((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->Serial_DebutEpreuve(); break;
        case 10: _t->Serial_DeplacementG(); break;
        case 11: _t->Tourelle_Release(); break;
        case 12: _t->Analyse_Commande_Perso(); break;
        default: ;
        }
    }
}

const QMetaObject mainFenetre::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_mainFenetre.data,
      qt_meta_data_mainFenetre,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *mainFenetre::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mainFenetre::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mainFenetre.stringdata0))
        return static_cast<void*>(const_cast< mainFenetre*>(this));
    return QWidget::qt_metacast(_clname);
}

int mainFenetre::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
