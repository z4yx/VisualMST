#include "algorithmworker.h"


AlgorithmWorker::AlgorithmWorker(AbstructMSTAlgo *algo, const QMap<int,QPointF> *vertexes) : mVertexes(vertexes), mAlgo(algo)
{

}

void AlgorithmWorker::run()
{
    mVertexList = mVertexes->values();
    mAlgo->findEuclideanMST(mVertexList);
}
