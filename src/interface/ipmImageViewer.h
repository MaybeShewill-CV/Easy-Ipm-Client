/************************************************
* Copyright 2018 Baidu Inc. All Rights Reserved.
* Author: Luo Yao
* File: ipmImageViewer.h
* Date: 18-12-29 下午5:28
************************************************/

#pragma once

#include <QObject>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QMenu>

// Own Ipm Image Viewer

const double DEFAULT_ZOOM_CTRL_FACTOR = 1.15;

class IpmImageViewer : public QGraphicsView
{
    Q_OBJECT

public:

    IpmImageViewer(bool isContextualMenu=true, QWidget *parent=nullptr);
    ~IpmImageViewer();

    void set_image(const QImage &image);


    void set_image_from_raw_data(const uchar *data, int width, int height,
                             bool mirrorHorizontally=false, bool mirrorVertically=false);

    inline bool is_image_viewer_empty() {
        return _m_pixmap.isNull() || _m_pixmap.height() == 0 || _m_pixmap.width() == 0;
    }

    inline void set_zoom_ctrl_factor(const double factor) {
        _m_zoom_ctrl_factor = factor;
    }

    inline QPointF get_mouse_coordinates() const {
        return _m_mouse_point;
    }

    inline QColor get_mouse_location_qcolor() const {
        return _m_mouse_location_qcolor;
    }

public slots:

    void fit_image(); // adaptive fit the imagw viewer window

signals:
    void report_mouse_scene_information(); // report the mouse coordinates on the scene

protected:

    virtual void drawOnImage(QPainter *painter, QSize imageSize);

    virtual void drawInViewPort(QPainter *painter, QSize portSize);

    virtual void drawForeground(QPainter *painter, const QRectF &rect);

    virtual QString setToolTipText(QPoint imageCoordinates);

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void wheelEvent(QWheelEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);

    virtual void resizeEvent(QResizeEvent *event);

protected slots:

    virtual void showContextMenu(const QPoint & pos);

private:

    // Scene where the image is drawn
    QGraphicsScene *_m_scene;

    // Pixmap item containing the image
    QGraphicsPixmapItem *_m_pixmapitem;

    // Size of the current image
    QSize _m_image_size;

    // Zoom factor when the CTRL key is pressed
    double _m_zoom_ctrl_factor;

    // Current pixmap
    QPixmap _m_pixmap;

    // mouse coordinates
    QPointF _m_mouse_point;

    // mouse location rgb value
    QColor _m_mouse_location_qcolor;
};
