#ifndef GRAPHICSVERTEXITEM_H
#define GRAPHICSVERTEXITEM_H

#include <QGraphicsEllipseItem>
#include <QPen>
#include <QBrush>

class GraphManager;

class GraphicsVertexItem : public QGraphicsEllipseItem
{
public:
    GraphicsVertexItem(qreal x, qreal y, qreal w, qreal h, int id, GraphManager* mgr);
    int getVertexId(){
        return mId;
    }

protected:

//    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void	 mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
    void     paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget);

private:
    int mId;
    GraphManager* mManager;
    QPointF mLastDelta;
};

#endif // GRAPHICSVERTEXITEM_H
