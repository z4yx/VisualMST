#ifndef VERTEXS_H
#define VERTEXS_H

#include <QSet>
#include <QPointF>
#include <QObject>

class MSTVertexes : public QObject
{
    Q_OBJECT
private:
    QList<QPointF> mVertexes;
    bool changed;
public:
    MSTVertexes();

    void clearDocuments();
    const QList<QPointF>& getVertexes();
    void loadVertexesFromFile(QString fileName);
    void saveVertexesToFile(QString fileName);
    bool isChanged();
signals:
    void newVertexesLoaded(const QList<QPointF>&);
public slots:
    void changeVertexPos(int index, QPointF delta);
};

#endif // VERTEXS_H
