#include "algorithmworker.h"


AlgorithmWorker::AlgorithmWorker(AbstructMSTAlgo *algo, const QList<QPointF> &vertexes) : mVertexes(vertexes), mAlgo(algo)
{

}

void AlgorithmWorker::run()
{
    mAlgo->findEuclideanMST(mVertexes);
}
