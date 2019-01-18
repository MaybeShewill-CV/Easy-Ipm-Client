/************************************************
* Copyright 2019 Baidu Inc. All Rights Reserved.
* Author: Luo Yao (luoyao@baidu.com)
* File: qWaitDialog.cpp
* Date: 2019-1-18
************************************************/

#include "qWaitDialog.h"

#include <QApplication>

#include "common/log_utils/beecLogger.h"
#include "common/file_system_utils/file_system_processor.h"

using beec::common::file_system_utils::FileSystemProcessor;

QWaitDialog::QWaitDialog(QWidget *parent) : QDialog (parent) {

    this->setFixedSize(150, 150);

    //设置透明度
    this->setWindowOpacity(0.8);

    //取消对话框标题
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setStyleSheet("background-color:transparent;");

    //设置背景色为淡蓝色
    _m_background = new QFrame(this);
    _m_background->setStyleSheet("background-color: rgb(55, 135, 215); border-radius:10px;");
    _m_background->setGeometry(0, 0, 150, 150);

    _m_label = new QLabel(_m_background);
    _m_label->setStyleSheet("background-color:transparent;");
    _m_label->setGeometry(25, 10, 100, 100);

    _m_movie = new QMovie("../images/wait.gif");
    _m_label->setScaledContents(true);
    _m_label->setMovie(_m_movie);

    _m_tip_label = new QLabel(_m_background);
    _m_tip_label->setText(tr("Waiting..."));
    _m_tip_label->setStyleSheet("color: white;background-color: transparent;");
    _m_tip_label->setGeometry(0, 125, 150, 25);

    _m_movie->start();
}

QWaitDialog::QWaitDialog(const QString &title, QWidget *parent) : QDialog (parent) {

    this->setFixedSize(150, 150);

    //设置透明度
    this->setWindowOpacity(0.8);

    //取消对话框标题
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setStyleSheet("background-color:transparent;");

    //设置背景色为淡蓝色
    _m_background = new QFrame(this);
    _m_background->setStyleSheet("background-color: rgb(55, 135, 215); border-radius:10px;");
    _m_background->setGeometry(0, 0, 150, 150);

    _m_label = new QLabel(_m_background);
    _m_label->setStyleSheet("background-color:transparent;");
    _m_label->setGeometry(25, 10, 100, 100);

    _m_movie = new QMovie("../images/wait.gif");
    _m_label->setScaledContents(true);
    _m_label->setMovie(_m_movie);

    _m_tip_label = new QLabel(_m_background);
    _m_tip_label->setText(title);
    _m_tip_label->setStyleSheet("color: white;background-color: transparent;");
    _m_tip_label->setGeometry(0, 125, 150, 25);

    _m_movie->start();
}

void QWaitDialog::mousePressEvent(QMouseEvent *event) {

    if (event->buttons() == Qt::LeftButton) {
        _m_is_mouse_press = true;
    }

    _m_move_point = event->globalPos() - this->pos();

    return QDialog::mouseMoveEvent(event);
}

void QWaitDialog::mouseMoveEvent(QMouseEvent *event) {

    if (_m_is_mouse_press &&
            (event->buttons() == Qt::LeftButton) &&
            (event->globalPos() - _m_move_point).manhattanLength() > QApplication::startDragDistance()) {

        this->move(event->globalPos() - _m_move_point);
        _m_move_point = event->globalPos() - pos();
    }

    return QDialog::mouseMoveEvent(event);
}

void QWaitDialog::mouseReleaseEvent(QMouseEvent *event) {

    _m_is_mouse_press = false;
    _m_move_point = QPoint(0, 0);

    return QDialog::mouseReleaseEvent(event);
}

QWaitDialog::~QWaitDialog(){

    delete _m_label;
    delete _m_movie;
    delete _m_tip_label;
    delete _m_background;

    _m_label = nullptr;
    _m_movie = nullptr;
    _m_tip_label = nullptr;
    _m_background = nullptr;
}
