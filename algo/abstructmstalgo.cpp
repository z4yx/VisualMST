#include "abstructmstalgo.h"

#include <cmath>


qreal AbstructMSTAlgo::hypot(const QPointF &a, const QPointF &b) const
{
    QPointF t(a);
    t -= b;
    return std::sqrt(t.x()*t.x() + t.y()*t.y());
}
