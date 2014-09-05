#ifndef ALGORITHMWORKER_H
#define ALGORITHMWORKER_H

#include <QThread>
#include <QMap>
#include "abstructmstalgo.h"


class AlgorithmWorker : public QThread
{
    Q_OBJECT
public:
    AlgorithmWorker(AbstructMSTAlgo* algo, const QMap<int,QPointF> *vertexes);
protected:
    void run();
private:
    AbstructMSTAlgo *mAlgo;
    const QMap<int,QPointF> *mVertexes;
    QList<QPointF> mVertexList;
};

#endif // ALGORITHMWORKER_H
