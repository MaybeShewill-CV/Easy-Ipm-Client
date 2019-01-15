/****************************************************************************
** Meta object code from reading C++ file 'ipmImageViewer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/interface/ipmImageViewer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ipmImageViewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_IpmImageViewer_t {
    QByteArrayData data[6];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IpmImageViewer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IpmImageViewer_t qt_meta_stringdata_IpmImageViewer = {
    {
QT_MOC_LITERAL(0, 0, 14), // "IpmImageViewer"
QT_MOC_LITERAL(1, 15, 30), // "report_mouse_scene_information"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 9), // "fit_image"
QT_MOC_LITERAL(4, 57, 15), // "showContextMenu"
QT_MOC_LITERAL(5, 73, 3) // "pos"

    },
    "IpmImageViewer\0report_mouse_scene_information\0"
    "\0fit_image\0showContextMenu\0pos"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IpmImageViewer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   30,    2, 0x0a /* Public */,
       4,    1,   31,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    5,

       0        // eod
};

void IpmImageViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        IpmImageViewer *_t = static_cast<IpmImageViewer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->report_mouse_scene_information(); break;
        case 1: _t->fit_image(); break;
        case 2: _t->showContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (IpmImageViewer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&IpmImageViewer::report_mouse_scene_information)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject IpmImageViewer::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_IpmImageViewer.data,
      qt_meta_data_IpmImageViewer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *IpmImageViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IpmImageViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_IpmImageViewer.stringdata0))
        return static_cast<void*>(const_cast< IpmImageViewer*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int IpmImageViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void IpmImageViewer::report_mouse_scene_information()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
