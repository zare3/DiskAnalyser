/****************************************************************************
** Meta object code from reading C++ file 'fileexplorer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "fileexplorer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fileexplorer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FileExplorer_t {
    QByteArrayData data[17];
    char stringdata[296];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FileExplorer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FileExplorer_t qt_meta_stringdata_FileExplorer = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 23),
QT_MOC_LITERAL(2, 37, 0),
QT_MOC_LITERAL(3, 38, 5),
QT_MOC_LITERAL(4, 44, 17),
QT_MOC_LITERAL(5, 62, 17),
QT_MOC_LITERAL(6, 80, 15),
QT_MOC_LITERAL(7, 96, 43),
QT_MOC_LITERAL(8, 140, 20),
QT_MOC_LITERAL(9, 161, 17),
QT_MOC_LITERAL(10, 179, 41),
QT_MOC_LITERAL(11, 221, 11),
QT_MOC_LITERAL(12, 233, 10),
QT_MOC_LITERAL(13, 244, 10),
QT_MOC_LITERAL(14, 255, 12),
QT_MOC_LITERAL(15, 268, 14),
QT_MOC_LITERAL(16, 283, 12)
    },
    "FileExplorer\0onListItemDoubleClicked\0"
    "\0index\0onTreeItemClicked\0onListItemClicked\0"
    "upButtonPressed\0"
    "on_actionCheck_Disk_Fragmentation_triggered\0"
    "forwardButtonPressed\0backButtonPressed\0"
    "on_actionCheck_Security_Threats_triggered\0"
    "dirInfoSlot\0getExtSlot\0getOwnSlot\0"
    "getGroupSlot\0Update_JSGraph\0Expose_To_Js"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FileExplorer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x08 /* Private */,
       4,    1,   87,    2, 0x08 /* Private */,
       5,    1,   90,    2, 0x08 /* Private */,
       6,    0,   93,    2, 0x08 /* Private */,
       7,    0,   94,    2, 0x08 /* Private */,
       8,    0,   95,    2, 0x08 /* Private */,
       9,    0,   96,    2, 0x08 /* Private */,
      10,    0,   97,    2, 0x08 /* Private */,
      11,    1,   98,    2, 0x0a /* Public */,
      12,    1,  101,    2, 0x0a /* Public */,
      13,    1,  104,    2, 0x0a /* Public */,
      14,    1,  107,    2, 0x0a /* Public */,
      15,    1,  110,    2, 0x0a /* Public */,
      16,    0,  113,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void,

       0        // eod
};

void FileExplorer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FileExplorer *_t = static_cast<FileExplorer *>(_o);
        switch (_id) {
        case 0: _t->onListItemDoubleClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 1: _t->onTreeItemClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 2: _t->onListItemClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 3: _t->upButtonPressed(); break;
        case 4: _t->on_actionCheck_Disk_Fragmentation_triggered(); break;
        case 5: _t->forwardButtonPressed(); break;
        case 6: _t->backButtonPressed(); break;
        case 7: _t->on_actionCheck_Security_Threats_triggered(); break;
        case 8: _t->dirInfoSlot((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 9: _t->getExtSlot((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 10: _t->getOwnSlot((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 11: _t->getGroupSlot((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 12: _t->Update_JSGraph((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 13: _t->Expose_To_Js(); break;
        default: ;
        }
    }
}

const QMetaObject FileExplorer::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_FileExplorer.data,
      qt_meta_data_FileExplorer,  qt_static_metacall, 0, 0}
};


const QMetaObject *FileExplorer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileExplorer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FileExplorer.stringdata))
        return static_cast<void*>(const_cast< FileExplorer*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int FileExplorer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
