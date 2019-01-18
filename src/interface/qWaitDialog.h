/************************************************
* Copyright 2019 Baidu Inc. All Rights Reserved.
* Author: Luo Yao (luoyao@baidu.com)
* File: qWaitDialog.h
* Date: 2019-1-18
************************************************/

#pragma once

#include <QDialog>
#include <QLabel>
#include <QMovie>
#include <QFrame>
#include <QMouseEvent>

class QWaitDialog : public QDialog {

     Q_OBJECT

public:

    explicit QWaitDialog(QWidget *parent=nullptr);
    QWaitDialog(const QString &title, QWidget *parent=nullptr);

    ~QWaitDialog();

private:
    QMovie *_m_movie;
    QLabel *_m_label;
    QLabel *_m_tip_label;
    QFrame *_m_background;

    bool _m_is_mouse_press = false;
    QPoint _m_move_point = QPoint(0, 0);

protected:

    // implement window move by press mouse
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
};
