#ifndef PRIMALGORITHM_H
#define PRIMALGORITHM_H

#include "abstructmstalgo.h"

class PrimAlgorithm : public AbstructMSTAlgo
{
    Q_OBJECT
public:
    void doFindEuclideanMST(const QList<QPointF>& vertexes);
    const QList<QLineF>& getMSTEdges();
private:

    QList<QLineF> result;
};

#endif // PRIMALGORITHM_H
