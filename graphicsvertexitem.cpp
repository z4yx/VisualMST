#include "graphicsvertexitem.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "graphmanager.h"

GraphicsVertexItem::GraphicsVertexItem(qreal x, qreal y, qreal w, qreal h, int id, GraphManager* mgr):
    QGraphicsEllipseItem(x, y, w, h, 0),
    mId(id),
    mManager(mgr)
{

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
