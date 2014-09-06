#include "primalgorithm.h"
#include <QDebug>


void PrimAlgorithm::doFindEuclideanMST(const QList<QPointF> &vertexes)
{
    result.clear();

    int n = vertexes.size();
    if(n == 0)
        return;

    int progress = 0;
    int progress_slice = n/100, progress_update = 0;

    bool *visited = new bool[n];
    qreal *distances = new qreal[n];
    int *pre = new int[n];
    qreal MAX_DISTANCE = std::numeric_limits<qreal>::max()/3;
    int cur = 0;

    for(int i=0; i<n; i++)
        visited[i] = false;
    for(int i=0; i<n; i++){
        distances[i] = hypot(vertexes[cur], vertexes[i]);
        pre[i] = cur;
    }
    distances[cur] = 0;
    visited[cur] = true;
    pre[cur] = -1;

    for(int i=0; i<n; i++){
        qreal minimal = MAX_DISTANCE;
        cur = -1;
        for(int j=0; j<n; j++)
            if(!visited[j] && distances[j] < minimal){
                minimal = distances[j];
                cur = j;
            }
        if(cur == -1){
            qDebug() << "cur == -1";
            break;
        }
        visited[cur] = true;
        result.append(QLineF(vertexes[cur], vertexes[pre[cur]]));
        for(int j=0; j<n; j++){
            if(!visited[j]){
                qreal dist = hypot(vertexes[cur], vertexes[j]);
                if(dist < distances[j]){
                    distances[j] = dist;
                    pre[j] = cur;
                }
            }
        }
        if(i == progress_update){
            emit progressUpdated(progress);
            progress_update += progress_slice;
            progress++;
        }
    }
    if(progress < 100)
        emit progressUpdated(100);
    delete[] pre;
    delete[] distances;
    delete[] visited;
}



const QList<QLineF> &PrimAlgorithm::getMSTEdges()
{
    return result;
}
