#include "graphicsvertexitem.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QRectF>
#include "graphmanager.h"

GraphicsVertexItem::GraphicsVertexItem(qreal x, qreal y, qreal w, qreal h, int id, GraphManager* mgr):
    QGraphicsEllipseItem(x, y, w, h, 0),
    mId(id),
    mManager(mgr)
{
    setBrush(QBrush(QColor(Qt::black)));
    setPen(QPen(QColor(Qt::transparent)));
}


//QVariant GraphicsVertexItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
//{
//    if(change == ItemPositionHasChanged) {
//        QPointF pos = value.toPointF();
//        qDebug() << pos;
//    }

//    return QGraphicsEllipseItem::itemChange(change, value);
//}


void GraphicsVertexItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsEllipseItem::mouseReleaseEvent(event);
    QPointF p = pos();
    mManager->itemPosChanged(mId, p-mLastDelta);
    mLastDelta = p;
}

void GraphicsVertexItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(option->state & QStyle::State_Selected){
        QBrush b = brush();
        b.setColor(QColor(Qt::red));
        painter->setBrush(b);
    }else{
        painter->setBrush(brush());
    }
    painter->setPen(pen());

    painter->drawEllipse(rect());
}
