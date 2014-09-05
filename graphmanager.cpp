#include "graphmanager.h"
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QDebug>

#include "graphicsvertexitem.h"

#define VERTEX_SIZE 0.2
#define EDGE_WIDTH  0.03

GraphManager::GraphManager(MSTGraphicsView *view)
{
    mView = view;

    scene = new QGraphicsScene(mView);

    mVertexGroup = scene->createItemGroup(QList<QGraphicsItem *>());
    mMSTEdgeGroup = scene->createItemGroup(QList<QGraphicsItem *>());
    mDelaunayEdgeGroup = scene->createItemGroup(QList<QGraphicsItem *>());
    mVoronoiEdgeGroup = scene->createItemGroup(QList<QGraphicsItem *>());

    mVertexGroup->setZValue(ZValue_Vertexes);
    mMSTEdgeGroup->setZValue(ZValue_MST_Edges);
    mDelaunayEdgeGroup->setZValue(ZValue_Delaunay_Edges);
    mVoronoiEdgeGroup->setZValue(ZValue_Voronoi_Edges);

    mView->setScene(scene);
}

void GraphManager::drawEditableVertex(const QList<QPointF> &vtx)
{
    int i = 0;
    scene->clear();
    for(QList<QPointF>::const_iterator it = vtx.constBegin();
        it != vtx.constEnd();
        ++it){

        drawSingleVertex(*it, i++);
    }
}

void GraphManager::drawSingleVertex(QPointF point, int id)
{
    QBrush brush(Qt::SolidPattern);
    GraphicsVertexItem *pt;
    pt = new GraphicsVertexItem(point.x()-VERTEX_SIZE/2, point.y()-VERTEX_SIZE/2, VERTEX_SIZE, VERTEX_SIZE, id, this);
    pt->setZValue(ZValue_Vertexes);
    pt->setBrush(brush);
    pt->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable/*|QGraphicsItem::ItemSendsGeometryChanges*/);
//    pt->setAcceptHoverEvents(true);
    scene->addItem(pt);
}


void GraphManager::drawVertexes(const QList<QPointF> &vtx, bool visible)
{
    scene->removeItem(mVertexGroup);

    QList<QPointF>::const_iterator i = vtx.constBegin();
    QBrush brush(Qt::SolidPattern);
    while (i != vtx.constEnd()) {
        QGraphicsEllipseItem *pt;
        pt = new QGraphicsEllipseItem(i->x()-VERTEX_SIZE/2, i->y()-VERTEX_SIZE/2, VERTEX_SIZE, VERTEX_SIZE);
        pt->setZValue(ZValue_Vertexes);
        pt->setBrush(brush);
        mVertexGroup->addToGroup(pt);
        ++i;
    }
    mVertexGroup->setVisible(visible);
    scene->addItem(mVertexGroup);
}

void GraphManager::drawMSTEdges(const QList<QLineF> &edge, bool visible)
{
    scene->removeItem(mMSTEdgeGroup);

    QList<QLineF>::const_iterator i = edge.constBegin();
    QPen pen(QColor(255, 0, 0), EDGE_WIDTH/*, Qt::DotLine*/);
    while (i != edge.constEnd()) {
        QGraphicsLineItem *pt;
        pt = new QGraphicsLineItem(*i);
        pt->setZValue(ZValue_MST_Edges);
        pt->setPen(pen);
        mMSTEdgeGroup->addToGroup(pt);
        ++i;
    }
    mMSTEdgeGroup->setVisible(visible);
    scene->addItem(mMSTEdgeGroup);

}

void GraphManager::drawDelaunayEdges(const QList<QLineF> &edge, bool visible)
{
    scene->removeItem(mDelaunayEdgeGroup);

    QList<QLineF>::const_iterator i = edge.constBegin();
    QPen pen(QColor(), EDGE_WIDTH);
    while (i != edge.constEnd()) {
        QGraphicsLineItem *pt;
        pt = new QGraphicsLineItem(*i);
        pt->setZValue(ZValue_Delaunay_Edges);
        pt->setPen(pen);
        mDelaunayEdgeGroup->addToGroup(pt);
        ++i;
    }
    mDelaunayEdgeGroup->setVisible(visible);
    scene->addItem(mDelaunayEdgeGroup);
}

void GraphManager::drawVoronoiEdges(const QList<QLineF> &edge, const QRectF &rect, bool visible)
{
    scene->removeItem(mVoronoiEdgeGroup);

    QList<QLineF>::const_iterator i = edge.constBegin();
    QPen pen(QColor(0, 0, 255), EDGE_WIDTH);
    while (i != edge.constEnd()) {
        QGraphicsLineItem *pt;
        pt = new QGraphicsLineItem(*i);
        pt->setZValue(ZValue_Voronoi_Edges);
        pt->setPen(pen);
        mVoronoiEdgeGroup->addToGroup(pt);
        ++i;
    }
    QGraphicsRectItem *border = new QGraphicsRectItem(rect);
    pen.setStyle(Qt::DotLine);
    border->setPen(pen);
    mVoronoiEdgeGroup->addToGroup(border);

    mVoronoiEdgeGroup->setVisible(visible);
    scene->addItem(mVoronoiEdgeGroup);

}

void GraphManager::showVertexes(bool visible)
{
    mVertexGroup->setVisible(visible);
}

void GraphManager::showMSTEdges(bool visible)
{
    mMSTEdgeGroup->setVisible(visible);
}

void GraphManager::showDelaunayEdges(bool visible)
{
    mDelaunayEdgeGroup->setVisible(visible);
}

void GraphManager::showVoronoiEdges(bool visible)
{
    mVoronoiEdgeGroup->setVisible(visible);
}

void GraphManager::itemPosChanged(int id, QPointF delta)
{
    emit itemPosChangedEvent(id, delta);
}
