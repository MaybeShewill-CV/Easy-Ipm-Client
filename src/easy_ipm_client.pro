#-------------------------------------------------
#
# Project created by QtCreator 2018-12-18T15:53:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = easy_ipm_client
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    interface/main.cpp \
    interface/mainwindow.cpp \
    interface/ipmCamCalibParamParser.cpp \
    interface/ipmImageViewer.cpp \
    interface/ipmParameterParser.cpp \
    camera_model/cameraModel.cpp \
    camera_calibration/camerCalibrator.cpp \
    common/file_system_utils/file_system_processor.cpp \
    common/log_utils/beecLogger.cpp \
    tracefile_parser/frametimeParser.cpp \
    tracefile_parser/panotimebParser.cpp \
    ipm_transform_worker/ipmtransformworker.cpp

HEADERS += \
    interface/mainwindow.h \
    interface/ipmparameterparser.h \
    interface/ipmCamCalibParamParser.h \
    interface/ipmImageViewer.h \
    common/file_system_utils/file_system_processor.h \
    common/log_utils/beecLogger.h \
    tracefile_parser/frametimeParser.h \
    tracefile_parser/panotimebParser.h \
    camera_model/cameraModel.h \
    ipm_model/adaptiveIpmModel.h \
    ipm_transform_worker/ipmtransformworker.h \
    camera_calibration/camerCalibrator.h \

FORMS += \
    interface/mainwindow.ui

LIBS += \
    -lboost_system \
    -lboost_filesystem \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../easy_ipm_lib/release/release/ -leasy_ipm_model
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../easy_ipm_lib/release/debug/ -leasy_ipm_model
else:unix: LIBS += -L$$PWD/../easy_ipm_lib/release/ -leasy_ipm_model

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
