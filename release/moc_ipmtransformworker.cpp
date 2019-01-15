/****************************************************************************
** Meta object code from reading C++ file 'ipmtransformworker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/ipm_transform_worker/ipmtransformworker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ipmtransformworker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_IpmTransformWorker_t {
    QByteArrayData data[14];
    char stringdata0[258];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IpmTransformWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IpmTransformWorker_t qt_meta_stringdata_IpmTransformWorker = {
    {
QT_MOC_LITERAL(0, 0, 18), // "IpmTransformWorker"
QT_MOC_LITERAL(1, 19, 22), // "progress_value_changed"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 12), // "process_nums"
QT_MOC_LITERAL(4, 56, 22), // "progress_range_changed"
QT_MOC_LITERAL(5, 79, 3), // "min"
QT_MOC_LITERAL(6, 83, 3), // "max"
QT_MOC_LITERAL(7, 87, 19), // "is_process_finished"
QT_MOC_LITERAL(8, 107, 16), // "report_ipm_image"
QT_MOC_LITERAL(9, 124, 20), // "process_single_image"
QT_MOC_LITERAL(10, 145, 26), // "process_batch_image_static"
QT_MOC_LITERAL(11, 172, 27), // "process_batch_image_dynamic"
QT_MOC_LITERAL(12, 200, 23), // "terminate_batch_process"
QT_MOC_LITERAL(13, 224, 33) // "is_distoration_remap_matrix_l..."

    },
    "IpmTransformWorker\0progress_value_changed\0"
    "\0process_nums\0progress_range_changed\0"
    "min\0max\0is_process_finished\0"
    "report_ipm_image\0process_single_image\0"
    "process_batch_image_static\0"
    "process_batch_image_dynamic\0"
    "terminate_batch_process\0"
    "is_distoration_remap_matrix_loded"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IpmTransformWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    2,   62,    2, 0x06 /* Public */,
       7,    1,   67,    2, 0x06 /* Public */,
       8,    0,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   71,    2, 0x0a /* Public */,
      10,    0,   72,    2, 0x0a /* Public */,
      11,    0,   73,    2, 0x0a /* Public */,
      12,    0,   74,    2, 0x0a /* Public */,
      13,    0,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,

       0        // eod
};

void IpmTransformWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        IpmTransformWorker *_t = static_cast<IpmTransformWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->progress_value_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->progress_range_changed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->is_process_finished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->report_ipm_image(); break;
        case 4: _t->process_single_image(); break;
        case 5: _t->process_batch_image_static(); break;
        case 6: _t->process_batch_image_dynamic(); break;
        case 7: _t->terminate_batch_process(); break;
        case 8: { bool _r = _t->is_distoration_remap_matrix_loded();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (IpmTransformWorker::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&IpmTransformWorker::progress_value_changed)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (IpmTransformWorker::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&IpmTransformWorker::progress_range_changed)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (IpmTransformWorker::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&IpmTransformWorker::is_process_finished)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (IpmTransformWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&IpmTransformWorker::report_ipm_image)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject IpmTransformWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_IpmTransformWorker.data,
      qt_meta_data_IpmTransformWorker,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *IpmTransformWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IpmTransformWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_IpmTransformWorker.stringdata0))
        return static_cast<void*>(const_cast< IpmTransformWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int IpmTransformWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void IpmTransformWorker::progress_value_changed(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void IpmTransformWorker::progress_range_changed(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void IpmTransformWorker::is_process_finished(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void IpmTransformWorker::report_ipm_image()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
