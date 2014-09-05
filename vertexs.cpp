#include "vertexs.h"

#include <QFile>
#include <QTextStream>

MSTVertexes::MSTVertexes()
{
    changed = false;
}

void MSTVertexes::clearDocuments()
{
    mVertexes.clear();
    emit newVertexesLoaded(mVertexes);
    changed = false;
}

const QList<QPointF>& MSTVertexes::getVertexes()
{
    return mVertexes;
}

void MSTVertexes::loadVertexesFromFile(QString fileName)
{
    QFile file(fileName);
    if(file.open(QFile::ReadOnly)){
        QTextStream stream(&file);
        int n;
        qreal x, y;
        stream >> n;
        mVertexes.clear();
        while(n--){
            stream >> x >> y;
            mVertexes.append(QPointF(x, y));
        }
        emit newVertexesLoaded(mVertexes);
        changed = false;
    }
}

void MSTVertexes::saveVertexesToFile(QString fileName)
{
    QFile file(fileName);
    if(file.open(QFile::Truncate|QFile::WriteOnly)){
        QTextStream stream(&file);
        int n = mVertexes.size();
        stream << n << '\n';

        QList<QPointF>::const_iterator i = mVertexes.constBegin();
        while (i != mVertexes.constEnd()) {
            stream << i->x() << ' ' << i->y() << '\n';
            ++i;
        }
    }
    changed = false;
}

bool MSTVertexes::isChanged()
{
    return changed;
}

void MSTVertexes::changeVertexPos(int index, QPointF delta)
{
    mVertexes[index] += delta;
    changed = true;
}

void MSTVertexes::newVertex(int &newIndex, QPointF pt)
{
    newIndex = mVertexes.size();
    mVertexes.append(pt);
    changed = true;
}
