/****************************************************************************
** Meta object code from reading C++ file 'checkdiskfragmentation.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "checkdiskfragmentation.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'checkdiskfragmentation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CheckDiskFragmentation_t {
    QByteArrayData data[9];
    char stringdata[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CheckDiskFragmentation_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CheckDiskFragmentation_t qt_meta_stringdata_CheckDiskFragmentation = {
    {
QT_MOC_LITERAL(0, 0, 22),
QT_MOC_LITERAL(1, 23, 38),
QT_MOC_LITERAL(2, 62, 0),
QT_MOC_LITERAL(3, 63, 4),
QT_MOC_LITERAL(4, 68, 25),
QT_MOC_LITERAL(5, 94, 21),
QT_MOC_LITERAL(6, 116, 7),
QT_MOC_LITERAL(7, 124, 11),
QT_MOC_LITERAL(8, 136, 11)
    },
    "CheckDiskFragmentation\0"
    "on_prtitionsCmboBx_currentIndexChanged\0"
    "\0arg1\0fragmentationCmndFinished\0"
    "getDrivesCmndFinished\0hideAll\0showLoading\0"
    "hideLoading"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CheckDiskFragmentation[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x08 /* Private */,
       4,    1,   47,    2, 0x08 /* Private */,
       5,    1,   50,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CheckDiskFragmentation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CheckDiskFragmentation *_t = static_cast<CheckDiskFragmentation *>(_o);
        switch (_id) {
        case 0: _t->on_prtitionsCmboBx_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->fragmentationCmndFinished((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->getDrivesCmndFinished((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->hideAll(); break;
        case 4: _t->showLoading(); break;
        case 5: _t->hideLoading(); break;
        default: ;
        }
    }
}

const QMetaObject CheckDiskFragmentation::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CheckDiskFragmentation.data,
      qt_meta_data_CheckDiskFragmentation,  qt_static_metacall, 0, 0}
};


const QMetaObject *CheckDiskFragmentation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CheckDiskFragmentation::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CheckDiskFragmentation.stringdata))
        return static_cast<void*>(const_cast< CheckDiskFragmentation*>(this));
    return QDialog::qt_metacast(_clname);
}

int CheckDiskFragmentation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
