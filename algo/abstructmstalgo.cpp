#include "abstructmstalgo.h"

#include <cmath>
#include <QElapsedTimer>
#include <QDebug>

void AbstructMSTAlgo::findEuclideanMST(const QList<QPointF> &vertexes)
{
    QElapsedTimer timer;
    timer.start();
    doFindEuclideanMST(vertexes);
    timeUsage = timer.elapsed();
    qDebug() << "Elapsed" << timeUsage << "ms";
}

qint64 AbstructMSTAlgo::getTimeUsage()
{
    return timeUsage;
}

qreal AbstructMSTAlgo::hypot(const QPointF &a, const QPointF &b) const
{
    QPointF t(a);
    t -= b;
    return std::sqrt(t.x()*t.x() + t.y()*t.y());
}
