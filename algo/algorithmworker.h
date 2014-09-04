#ifndef ALGORITHMWORKER_H
#define ALGORITHMWORKER_H

#include <QThread>
#include "abstructmstalgo.h"


class AlgorithmWorker : public QThread
{
    Q_OBJECT
public:
    AlgorithmWorker(AbstructMSTAlgo* algo, const QList<QPointF> *vertexes);
protected:
    void run();
private:
    AbstructMSTAlgo *mAlgo;
    const QList<QPointF> *mVertexes;
};

#endif // ALGORITHMWORKER_H
