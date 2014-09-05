#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H

#include "view.h"
#include <QGraphicsScene>
#include <QMap>

class GraphManager : public QObject
{
    Q_OBJECT

private:
    enum CascadingOrder{ZValue_Voronoi_Edges, ZValue_Delaunay_Edges, ZValue_MST_Edges, ZValue_Vertexes};
    MSTGraphicsView *mView;
    QGraphicsScene *scene;
    QGraphicsItemGroup *mVertexGroup, *mMSTEdgeGroup, *mVoronoiEdgeGroup, *mDelaunayEdgeGroup;

public:
    GraphManager(MSTGraphicsView *view);

    void drawSingleVertex(QPointF point, int id);

    void drawVertexes(const QMap<int,QPointF>&, bool visible = true);
    void drawMSTEdges(const QList<QLineF>&, bool visible = true);
    void drawDelaunayEdges(const QList<QLineF>&, bool visible = true);
    void drawVoronoiEdges(const QList<QLineF>&, const QRectF &rect, bool visible = true);

    void showVertexes(bool visible = true);
    void showMSTEdges(bool visible = true);
    void showDelaunayEdges(bool visible = true);
    void showVoronoiEdges(bool visible = true);

    void itemPosChanged(int id, QPointF pos);

    void removeSelectedItem();
signals:
    void itemPosChangedEvent(int id, QPointF delta);
    void itemDeleted(int id);
public slots:
    void drawEditableVertex(const QMap<int,QPointF>&);
};

#endif // GRAPHMANAGER_H
