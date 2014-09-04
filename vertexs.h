#ifndef VERTEXS_H
#define VERTEXS_H

#include <QSet>
#include <QPointF>

class MSTVertexes
{
    QList<QPointF> mVertexes;
    bool changed;
public:
    MSTVertexes();

    void clearVertexes();
    const QList<QPointF>& getVertexes();
    void loadVertexesFromFile(QString fileName);
    void saveVertexesToFile(QString fileName);
    bool isChanged();
};

#endif // VERTEXS_H
