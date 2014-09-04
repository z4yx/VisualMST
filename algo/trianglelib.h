#ifndef TRIANGLELIB_H
#define TRIANGLELIB_H

#include "abstructmstalgo.h"
#include <QPair>
#include <QRect>
#include <QVector>

struct triangulateio;

class TriangleLib : public AbstructMSTAlgo
{
    Q_OBJECT
public:
    const QList<QLineF> findEuclideanMST(const QList<QPointF>& vertexes);
    const QList<QLineF>& getVoronoiEdges(QRectF &outBorder);
    const QList<QLineF>& getDelaunayEdges();
private:

    typedef QPair<qreal,QPair<int,int> >  edges_t;
    QList<QLineF> VoronoiEdges, DelaunayEdges;
    QVector<edges_t> mEdges;
    QRectF mBorder;
    void triangleLibProcess(const QList<QPointF>& vertexes);
    void calcVoronoiBorder(const triangulateio &vorout);
    void saveVoronoiGraph(const triangulateio &vorout);

    void kruskal(QList<QLineF>& result, const QList<QPointF> &);

    int unionFind(int a, int *s) const;

    static bool compareEdge(edges_t a, edges_t b);
};

#endif // TRIANGLELIB_H
