#ifndef VERTEXS_H
#define VERTEXS_H

#include <QMap>
#include <QPointF>
#include <QObject>

class MSTVertexes : public QObject
{
    Q_OBJECT
private:
    QMap<int,QPointF> mVertexes;
    bool changed;
    int idGenerator;
public:
    MSTVertexes();

    void clearDocuments();
    const QMap<int,QPointF>& getVertexes();
    void loadVertexesFromFile(QString fileName);
    void saveVertexesToFile(QString fileName);
    bool isChanged();
signals:
    void newVertexesLoaded(const QMap<int,QPointF>&);
public slots:
    void changeVertexPos(int index, QPointF delta);
    void newVertex(int &newIndex, QPointF pt);
    void deleteVertex(int index);
};

#endif // VERTEXS_H
