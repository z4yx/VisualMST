#ifndef ABSTRUCTMSTALGO_H
#define ABSTRUCTMSTALGO_H

#include <QObject>
#include <QList>
#include <QLineF>
#include <QPointF>

class AbstructMSTAlgo : public QObject
{
    Q_OBJECT
public:
    virtual void findEuclideanMST(const QList<QPointF>& vertexes) = 0;
    virtual const QList<QLineF>& getMSTEdges() = 0;
protected:
    qreal hypot(const QPointF &a, const QPointF &b) const;
signals:
    void progressUpdated(int progress);
};

#endif // ABSTRUCTMSTALGO_H
