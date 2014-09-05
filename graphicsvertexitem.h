#ifndef GRAPHICSVERTEXITEM_H
#define GRAPHICSVERTEXITEM_H

#include <QGraphicsEllipseItem>

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

private:
    int mId;
    GraphManager* mManager;
    QPointF mLastDelta;
};

#endif // GRAPHICSVERTEXITEM_H
