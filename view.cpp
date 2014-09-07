/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "view.h"

#include <QtGui>
//#ifndef QT_NO_OPENGL
//#include <QtOpenGL>
//#endif

#include <qmath.h>

void MSTGraphicsView::wheelEvent(QWheelEvent *e)
{
    if (e->modifiers() & Qt::ControlModifier) {
        qreal delta = qAbs(e->delta());
        delta /= 10000;
        if (e->delta() > 0)
            zoomIn(delta);
        else
            zoomOut(delta);
        e->accept();
    } else {
        QGraphicsView::wheelEvent(e);
    }
}

void MSTGraphicsView::mousePressEvent(QMouseEvent *e)
{
    if(mCurMode == DrawPointMode && e->button() == Qt::LeftButton){
        QPointF pt = mapToScene(e->pos());
        qDebug() << pt;
        emit newPointEvent(pt);
    }else{
        QGraphicsView::mousePressEvent(e);
    }
}


void MSTGraphicsView::zoomIn(qreal val)
{
    zoom += val;
    setupMatrix();
}

void MSTGraphicsView::zoomOut(qreal val)
{
    zoom -= val;
    setupMatrix();
}

void MSTGraphicsView::setPointerMode(PointerMode mode)
{
    if(mode == MoveMode){
        setDragMode(QGraphicsView::ScrollHandDrag);
        setInteractive(false);
    }else if(mode == SelectMode){
        setDragMode(QGraphicsView::RubberBandDrag);
        setCursor(QCursor(Qt::ArrowCursor));
        setInteractive(true);
    }else if(mode == DrawPointMode){
        setDragMode(QGraphicsView::RubberBandDrag);
        setCursor(QCursor(Qt::CrossCursor));
        setInteractive(false);
    }
    mCurMode = mode;
}

void MSTGraphicsView::initView()
{
    zoom = 0.9;
    setRenderHint(QPainter::Antialiasing, false);
    setOptimizationFlags(QGraphicsView::DontSavePainterState);
    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    setPointerMode(SelectMode);

    setupMatrix();
}

void MSTGraphicsView::fitInView(const QRectF &rect, Qt::AspectRatioMode aspectRadioMode)
{
    QGraphicsView::fitInView(rect, aspectRadioMode);
    QMatrix mat = matrix();
    qDebug() << mat.m11() << mat.m22();
    zoom = qLn(mat.m11())/qLn(2)/5;
}


void MSTGraphicsView::resetView()
{
    setupMatrix();
    ensureVisible(QRectF(0, 0, 0, 0));
}

void MSTGraphicsView::setupMatrix()
{
    qreal scale = qPow(qreal(2), zoom * 5);

    QMatrix matrix;
    matrix.scale(scale, scale);
//    matrix.rotate(rotateSlider->value());

    setMatrix(matrix);
}

//void View::togglePointerMode()
//{
//    graphicsView->setDragMode(selectModeButton->isChecked()
//                              ? QGraphicsView::RubberBandDrag
//                              : QGraphicsView::ScrollHandDrag);
//    graphicsView->setInteractive(selectModeButton->isChecked());
//}

//void View::toggleOpenGL()
//{
//#ifndef QT_NO_OPENGL
//    graphicsView->setViewport(openGlButton->isChecked() ? new QGLWidget(QGLFormat(QGL::SampleBuffers)) : new QWidget);
//#endif
//}

//void View::toggleAntialiasing()
//{
//    graphicsView->setRenderHint(QPainter::Antialiasing, antialiasButton->isChecked());
//}

