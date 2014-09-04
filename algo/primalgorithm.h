#ifndef PRIMALGORITHM_H
#define PRIMALGORITHM_H

#include "abstructmstalgo.h"

class PrimAlgorithm : public AbstructMSTAlgo
{
    Q_OBJECT
public:
    const QList<QLineF> findEuclideanMST(const QList<QPointF>& vertexes);
};

#endif // PRIMALGORITHM_H
