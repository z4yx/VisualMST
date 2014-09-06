#ifndef ABSTRUCTMSTALGO_H
#define ABSTRUCTMSTALGO_H

#include <QObject>
#include <QList>
#include <QLineF>
#include <QPointF>

class AbstructMSTAlgo : public QObject
{
    Q_OBJECT

    qint64 timeUsage;
public:
    void findEuclideanMST(const QList<QPointF>& vertexes);
    virtual const QList<QLineF>& getMSTEdges() = 0;
    qint64 getTimeUsage();
protected:
    virtual void doFindEuclideanMST(const QList<QPointF>& vertexes) = 0;
    qreal hypot(const QPointF &a, const QPointF &b) const;
signals:
    void progressUpdated(int progress);
};

#endif // ABSTRUCTMSTALGO_H
