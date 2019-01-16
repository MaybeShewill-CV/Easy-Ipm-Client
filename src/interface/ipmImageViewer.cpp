/************************************************
* Copyright 2018 Baidu Inc. All Rights Reserved.
* Author: Luo Yao
* File: ipmImageViewer.cpp
* Date: 18-12-27 下午4:23
************************************************/

#include "ipmImageViewer.h"

#include <QLabel>

#include "common/log_utils/beecLogger.h"

IpmImageViewer::IpmImageViewer(bool isContextualMenu, QWidget *parent) :
    QGraphicsView(parent) {

    // Set default zoom factors
    _m_zoom_ctrl_factor = DEFAULT_ZOOM_CTRL_FACTOR;

    // Create the scene
    _m_scene = new QGraphicsScene();

    // Allow mouse tracking even if no button is pressed
    this->setMouseTracking(true);

    // Add the scene to the QGraphicsView
    this->setScene(_m_scene);

    // Update all the view port when needed, otherwise, the drawInViewPort may experience trouble
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    // When zooming, the view stay centered over the mouse
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    this->setResizeAnchor(QGraphicsView::AnchorViewCenter);

    // Initialize contextual menu if requested
    if (isContextualMenu) {
        setContextMenuPolicy(Qt::CustomContextMenu);
        connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
    }

    // Add the default pixmap at startup
    _m_pixmapitem = _m_scene->addPixmap(_m_pixmap);
}

IpmImageViewer::~IpmImageViewer() {

    delete _m_pixmapitem;
    delete _m_scene;

    _m_pixmapitem = nullptr;
    _m_scene = nullptr;
}

void IpmImageViewer::showContextMenu(const QPoint & pos) {

    // Get the mouse position in the scene
    QPoint globalPos = mapToGlobal(pos);

    // Create the menu and add action
    QMenu contextMenu;
    contextMenu.addAction("reset view", this, SLOT(fit_image()));

    // Display the menu
    contextMenu.exec(globalPos);
}

void IpmImageViewer::set_image(const QImage &image) {

    // Update the pixmap in the scene
    _m_pixmap = QPixmap::fromImage(image);
    _m_pixmapitem->setPixmap(_m_pixmap);

    // Resize the scene (needed when the new image is smaller)
    _m_scene->setSceneRect(QRect(QPoint(0, 0), image.size()));

    // Store the image size
    _m_image_size = image.size();
}

void IpmImageViewer::set_image_from_raw_data(const uchar *data, int width, int height,
                                             bool mirrorHorizontally, bool mirrorVertically) {
    // Convert data into QImage
    QImage image(data, width, height, width * 3, QImage::Format_RGB888);

    // Update the pixmap in the scene
    _m_pixmap = QPixmap::fromImage(image.mirrored(mirrorHorizontally, mirrorVertically));
    _m_pixmapitem->setPixmap(_m_pixmap);

    // Resize the scene (needed is the new image is smaller)
    _m_scene->setSceneRect(QRect(QPoint(0, 0), image.size()));

    // Store the image size
    _m_image_size = image.size();
}

void IpmImageViewer::fit_image() {

    // Get current scroll bar policy
    Qt::ScrollBarPolicy	currentHorizontalPolicy = horizontalScrollBarPolicy();
    Qt::ScrollBarPolicy	currentverticalPolicy = verticalScrollBarPolicy();

    // Disable scroll bar to avoid a margin around the image
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Fit the scene in the QGraphicsView
    this->fitInView(_m_scene->sceneRect(), Qt::KeepAspectRatio);

    // Restaure scroll bar policy
    setHorizontalScrollBarPolicy(currentHorizontalPolicy);
    setVerticalScrollBarPolicy(currentverticalPolicy);
}

// Called when a mouse button is pressed
void IpmImageViewer::mousePressEvent(QMouseEvent *event) {

    // Drag mode : change the cursor's shape
    if (event->button() == Qt::LeftButton) {
       this->setDragMode(QGraphicsView::ScrollHandDrag);
    }

    QGraphicsView::mousePressEvent(event);
}

// Called when a mouse button is released
void IpmImageViewer::mouseReleaseEvent(QMouseEvent *event) {

    // Exit drag mode : change the cursor's shape
    if (event->button() == Qt::LeftButton) {
      this->setDragMode(QGraphicsView::NoDrag);
    }

    QGraphicsView::mouseReleaseEvent(event);
}

#ifndef QT_NO_WHEELEVENT

// Call when there is a scroll event (zoom in or zoom out)
void IpmImageViewer::wheelEvent(QWheelEvent *event) {

    // When zooming, the view stay centered over the mouse
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    if (event->modifiers() & Qt::ControlModifier) {

        if (event->delta() > 0) {
            // Zoom in
            scale(_m_zoom_ctrl_factor, _m_zoom_ctrl_factor);
        } else {
            // Zooming out
            scale(1.0 / _m_zoom_ctrl_factor, 1.0 / _m_zoom_ctrl_factor);
        }

        // The event is processed
        event->accept();
    } else {
        // Call the parent's function (for scrolling)
        QGraphicsView::wheelEvent(event);
    }
}

#endif

// Overload the mouse MoveEvent to display the tool tip
void IpmImageViewer::mouseMoveEvent(QMouseEvent *event) {

    // Get the coordinates of the mouse in the scene
    QPointF image_point = mapToScene(QPoint(event->x(), event->y()));

    // Call the function that create the tool tip
    setToolTip(setToolTipText(QPoint(static_cast<int>(image_point.x()),
                                     static_cast<int>(image_point.y()))));

    // Call the parent's function (for dragging)
    QGraphicsView::mouseMoveEvent(event);

    // set mouse coordinate
    _m_mouse_point = image_point;

    // set mouse location pixel value
    QPoint mouse_location(static_cast<int>(std::lround(_m_mouse_point.x())),
                          static_cast<int>(std::lround(_m_mouse_point.y())));

    if (mouse_location.x() <= 0 ||
            mouse_location.x() >= _m_pixmap.width() ||
            mouse_location.y() <= 0 ||
            mouse_location.y() >= _m_pixmap.height()) {

        _m_mouse_location_qcolor = QColor(0, 0, 0);
    } else {
        _m_mouse_location_qcolor = _m_pixmap.toImage().pixel(mouse_location.x(), mouse_location.y());
    }

    // emit report mouse scene information signal
    emit report_mouse_scene_information();
}

// Overload the function to draw over the image
void IpmImageViewer::drawForeground(QPainter *painter, const QRectF&) {

    // Call the function to draw over the image
    this->drawOnImage(painter, _m_image_size);

    // Reset transformation and call the function draw in the view port
    painter->resetTransform();

    // Call the function to draw in the view port
    this->drawInViewPort(painter, this->viewport()->size());
}

// Overloaded functionthat catch the resize event
void IpmImageViewer::resizeEvent(QResizeEvent *event) {

    // First call, the scene is created
    if (event->oldSize().width() == -1 || event->oldSize().height() == -1) {
        return;
    }

    // Get the previous rectangle of the scene in the viewport
    QPointF p1 = mapToScene(QPoint(0, 0));
    QPointF p2 = mapToScene(QPoint(event->oldSize().width(),event->oldSize().height()));

    // Stretch the rectangle around the scene
    if (p1.x() < 0) {
        p1.setX(0);
    }

    if (p1.y() < 0) {
        p1.setY(0);
    }
    if (p2.x() > _m_scene->width())
    {
        p2.setX(_m_scene->width());
    }
    if (p2.y() > _m_scene->height()) {
        p2.setY(_m_scene->height());
    }

    // Fit the previous area in the scene
    this->fitInView(QRect(p1.toPoint(), p2.toPoint()), Qt::KeepAspectRatio);
}

// Define the virtual function to avoid the "unused parameter" warning
QString IpmImageViewer::setToolTipText(QPoint imageCoordinates) {

    (void)imageCoordinates;
    return QString("");
}

// Define the virtual function to avoid the "unused parameter" warning
void IpmImageViewer::drawOnImage(QPainter* , QSize ) {

}

// Define the virtual function to avoid the "unused parameter" warning
void IpmImageViewer::drawInViewPort(QPainter* , QSize ) {

}

