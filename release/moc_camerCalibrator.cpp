/****************************************************************************
** Meta object code from reading C++ file 'camerCalibrator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/camera_calibration/camerCalibrator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'camerCalibrator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_beec__camera_calibration__CamerCalibrator_t {
    QByteArrayData data[15];
    char stringdata0[434];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_beec__camera_calibration__CamerCalibrator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_beec__camera_calibration__CamerCalibrator_t qt_meta_stringdata_beec__camera_calibration__CamerCalibrator = {
    {
QT_MOC_LITERAL(0, 0, 41), // "beec::camera_calibration::Cam..."
QT_MOC_LITERAL(1, 42, 31), // "report_extract_corners_progress"
QT_MOC_LITERAL(2, 74, 0), // ""
QT_MOC_LITERAL(3, 75, 37), // "report_evaluate_calib_result_..."
QT_MOC_LITERAL(4, 113, 32), // "report_vis_calib_result_progress"
QT_MOC_LITERAL(5, 146, 32), // "report_is_calib_process_finished"
QT_MOC_LITERAL(6, 179, 28), // "report_extract_corners_image"
QT_MOC_LITERAL(7, 208, 25), // "report_calib_result_image"
QT_MOC_LITERAL(8, 234, 31), // "report_calib_process_error_code"
QT_MOC_LITERAL(9, 266, 49), // "report_is_calib_para_calculat..."
QT_MOC_LITERAL(10, 316, 16), // "calibrate_camera"
QT_MOC_LITERAL(11, 333, 24), // "calibrate_fisheye_camera"
QT_MOC_LITERAL(12, 358, 21), // "distorate_plain_image"
QT_MOC_LITERAL(13, 380, 23), // "distorate_fisheye_image"
QT_MOC_LITERAL(14, 404, 29) // "terminate_calibration_process"

    },
    "beec::camera_calibration::CamerCalibrator\0"
    "report_extract_corners_progress\0\0"
    "report_evaluate_calib_result_progress\0"
    "report_vis_calib_result_progress\0"
    "report_is_calib_process_finished\0"
    "report_extract_corners_image\0"
    "report_calib_result_image\0"
    "report_calib_process_error_code\0"
    "report_is_calib_para_calculation_process_finished\0"
    "calibrate_camera\0calibrate_fisheye_camera\0"
    "distorate_plain_image\0distorate_fisheye_image\0"
    "terminate_calibration_process"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_beec__camera_calibration__CamerCalibrator[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       3,    1,   82,    2, 0x06 /* Public */,
       4,    1,   85,    2, 0x06 /* Public */,
       5,    1,   88,    2, 0x06 /* Public */,
       6,    0,   91,    2, 0x06 /* Public */,
       7,    0,   92,    2, 0x06 /* Public */,
       8,    1,   93,    2, 0x06 /* Public */,
       9,    1,   96,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   99,    2, 0x0a /* Public */,
      11,    0,  100,    2, 0x0a /* Public */,
      12,    0,  101,    2, 0x0a /* Public */,
      13,    0,  102,    2, 0x0a /* Public */,
      14,    0,  103,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void beec::camera_calibration::CamerCalibrator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CamerCalibrator *_t = static_cast<CamerCalibrator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->report_extract_corners_progress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->report_evaluate_calib_result_progress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->report_vis_calib_result_progress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->report_is_calib_process_finished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->report_extract_corners_image(); break;
        case 5: _t->report_calib_result_image(); break;
        case 6: _t->report_calib_process_error_code((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->report_is_calib_para_calculation_process_finished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->calibrate_camera(); break;
        case 9: _t->calibrate_fisheye_camera(); break;
        case 10: _t->distorate_plain_image(); break;
        case 11: _t->distorate_fisheye_image(); break;
        case 12: _t->terminate_calibration_process(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CamerCalibrator::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CamerCalibrator::report_extract_corners_progress)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CamerCalibrator::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CamerCalibrator::report_evaluate_calib_result_progress)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CamerCalibrator::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CamerCalibrator::report_vis_calib_result_progress)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (CamerCalibrator::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CamerCalibrator::report_is_calib_process_finished)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (CamerCalibrator::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CamerCalibrator::report_extract_corners_image)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (CamerCalibrator::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CamerCalibrator::report_calib_result_image)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (CamerCalibrator::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CamerCalibrator::report_calib_process_error_code)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (CamerCalibrator::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CamerCalibrator::report_is_calib_para_calculation_process_finished)) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject beec::camera_calibration::CamerCalibrator::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_beec__camera_calibration__CamerCalibrator.data,
      qt_meta_data_beec__camera_calibration__CamerCalibrator,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *beec::camera_calibration::CamerCalibrator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *beec::camera_calibration::CamerCalibrator::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_beec__camera_calibration__CamerCalibrator.stringdata0))
        return static_cast<void*>(const_cast< CamerCalibrator*>(this));
    return QObject::qt_metacast(_clname);
}

int beec::camera_calibration::CamerCalibrator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void beec::camera_calibration::CamerCalibrator::report_extract_corners_progress(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void beec::camera_calibration::CamerCalibrator::report_evaluate_calib_result_progress(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void beec::camera_calibration::CamerCalibrator::report_vis_calib_result_progress(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void beec::camera_calibration::CamerCalibrator::report_is_calib_process_finished(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void beec::camera_calibration::CamerCalibrator::report_extract_corners_image()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void beec::camera_calibration::CamerCalibrator::report_calib_result_image()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void beec::camera_calibration::CamerCalibrator::report_calib_process_error_code(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void beec::camera_calibration::CamerCalibrator::report_is_calib_para_calculation_process_finished(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
