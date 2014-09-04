#include "trianglelib.h"

extern "C"{
#include "triangle.h"
}

#include <cassert>
#include <QDebug>

#include <QtAlgorithms>
#include <QVector2D>

const QList<QLineF> TriangleLib::findEuclideanMST(const QList<QPointF> &vertexes)
{
    mEdges.clear();
    DelaunayEdges.clear();
    VoronoiEdges.clear();
    triangleLibProcess(vertexes);

    QList<QLineF> result;
    kruskal(result, vertexes);
    return result;
}

const QList<QLineF> &TriangleLib::getVoronoiEdges(QRectF &outBorder)
{
    outBorder = mBorder;
    return VoronoiEdges;
}

const QList<QLineF> &TriangleLib::getDelaunayEdges()
{
    return DelaunayEdges;
}

void TriangleLib::triangleLibProcess(const QList<QPointF> &vertexes)
{
    struct triangulateio in, mid, vorout;
    int n = vertexes.size();

    memset(&in, 0, sizeof(in));
    memset(&mid, 0, sizeof(mid));
    memset(&vorout, 0, sizeof(vorout));

    in.numberofpoints = n;
    in.numberofpointattributes = 0;
    in.pointlist = (REAL *) malloc(in.numberofpoints * 2 * sizeof(REAL));
    for(int i=0; i<n; i++){
        in.pointlist[i*2] = vertexes[i].x();
        in.pointlist[i*2+1] = vertexes[i].y();
    }
    in.pointattributelist = NULL;
    in.pointmarkerlist = NULL;
    in.numberofsegments = 0;
    in.numberofholes = 0;
    in.numberofregions = 0;
    in.regionlist = NULL;

    /* Make necessary initializations so that Triangle can return a */
    /*   triangulation in `mid' and a voronoi diagram in `vorout'.  */

    mid.pointlist = (REAL *) NULL;            /* Not needed if -N switch used. */
    /* Not needed if -N switch used or number of point attributes is zero: */
    mid.pointattributelist = (REAL *) NULL;
    mid.pointmarkerlist = (int *) NULL; /* Not needed if -N or -B switch used. */
    mid.trianglelist = (int *) NULL;          /* Not needed if -E switch used. */
    /* Not needed if -E switch used or number of triangle attributes is zero: */
    mid.triangleattributelist = (REAL *) NULL;
    mid.neighborlist = (int *) NULL;         /* Needed only if -n switch used. */
    /* Needed only if segments are output (-p or -c) and -P not used: */
    mid.segmentlist = (int *) NULL;
    /* Needed only if segments are output (-p or -c) and -P and -B not used: */
    mid.segmentmarkerlist = (int *) NULL;
    mid.edgelist = (int *) NULL;             /* Needed only if -e switch used. */
    mid.edgemarkerlist = (int *) NULL;   /* Needed if -e used and -B not used. */

    vorout.pointlist = (REAL *) NULL;        /* Needed only if -v switch used. */
    /* Needed only if -v switch used and number of attributes is not zero: */
    vorout.pointattributelist = (REAL *) NULL;
    vorout.edgelist = (int *) NULL;          /* Needed only if -v switch used. */
    vorout.normlist = (REAL *) NULL;         /* Needed only if -v switch used. */

    /* Triangulate the points.  Switches are chosen to read and write a  */
    /*   PSLG (p), preserve the convex hull (c), number everything from  */
    /*   zero (z), assign a regional attribute to each element (A), and  */
    /*   produce an edge list (e), a Voronoi diagram (v), and a triangle */
    /*   neighbor list (n).                                              */

    triangulate("zevQ", &in, &mid, &vorout);

    qDebug() << "Vertexes:" << in.numberofpoints;
    qDebug() << "DelaunayEdges:" << mid.numberofedges;
    qDebug() << "VoronoiPoints:" << vorout.numberofpoints;
    qDebug() << "VoronoiEdges:" << vorout.numberofedges;

    mEdges.reserve(mid.numberofedges);
    DelaunayEdges.reserve(mid.numberofedges);
    for (int i = 0; i < mid.numberofedges; ++i)
    {
        int a = mid.edgelist[i*2];
        int b = mid.edgelist[i*2+1];
        qreal l = hypot(vertexes[a], vertexes[b]);
        DelaunayEdges.append(QLineF(vertexes[a], vertexes[b]));
        mEdges.append(qMakePair(l, qMakePair(a, b)));
    }

    saveVoronoiGraph(vorout);

    free(in.pointlist);
    free(in.pointattributelist);
    free(in.pointmarkerlist);
    free(in.regionlist);
    free(mid.pointlist);
    free(mid.pointattributelist);
    free(mid.pointmarkerlist);
    free(mid.trianglelist);
    free(mid.triangleattributelist);
    free(mid.trianglearealist);
    free(mid.neighborlist);
    free(mid.segmentlist);
    free(mid.segmentmarkerlist);
    free(mid.edgelist);
    free(mid.edgemarkerlist);
    free(vorout.pointlist);
    free(vorout.pointattributelist);
    free(vorout.edgelist);
    free(vorout.normlist);
}

void TriangleLib::calcVoronoiBorder(const triangulateio &vorout)
{
    double maxx = std::numeric_limits<double>::min();
    double maxy = maxx;
    double minx = std::numeric_limits<double>::max();
    double miny = minx;

    for (int i = 0; i < vorout.numberofpoints; ++i)
    {
        maxx = std::max(maxx, vorout.pointlist[i*2]);
        minx = std::min(minx, vorout.pointlist[i*2]);
        maxy = std::max(maxy, vorout.pointlist[i*2+1]);
        miny = std::min(miny, vorout.pointlist[i*2+1]);
    }

    mBorder.setRect(minx, miny, maxx-minx, maxy-miny);
    mBorder.adjust(-mBorder.width()/3, -mBorder.height()/3,
                   mBorder.width()/3, mBorder.height()/3);
}

void TriangleLib::saveVoronoiGraph(const triangulateio &vorout)
{
    calcVoronoiBorder(vorout);

    VoronoiEdges.reserve(vorout.numberofedges);
    for (int i = 0; i < vorout.numberofedges; ++i)
    {
        int a = vorout.edgelist[i*2];
        int b = vorout.edgelist[i*2+1];
        if(b == -1){
            QPointF st(vorout.pointlist[a*2], vorout.pointlist[a*2+1]);
            QVector2D dir(vorout.normlist[i*2], vorout.normlist[i*2+1]);
            dir.normalize();
            dir *= 10;
            VoronoiEdges.append(QLineF(st, st + dir.toPointF()));
        }else{
            assert(a < vorout.numberofpoints && b < vorout.numberofpoints);
            VoronoiEdges.append(QLineF(
                vorout.pointlist[a*2], vorout.pointlist[a*2+1],
                vorout.pointlist[b*2], vorout.pointlist[b*2+1]));
        }
    }
}

void TriangleLib::kruskal(QList<QLineF> &result, const QList<QPointF> &vtx)
{
    int n = vtx.size();
    int *Union = new int[n];
    for(int i = 0; i < n; i++)
        Union[i] = i;

    qSort(mEdges.begin(), mEdges.end(), compareEdge);
    result.reserve(n-1);
    for(QVector<edges_t>::ConstIterator it = mEdges.constBegin();
        it != mEdges.constEnd();
        ++it) {

        QPair<int,int> e = it->second;
        int a = unionFind(e.first, Union);
        int b = unionFind(e.second, Union);
        if(a != b) {
            Union[a] = b;
            result.append(QLineF(vtx[e.first], vtx[e.second]));
        }
    }
    assert(result.size() == n-1);
}

int TriangleLib::unionFind(int a, int *s) const
{
    int i = a;
    while(s[i] != i) {
        i = s[i];
    }
    while(s[a] != a) {
        int j = s[a];
        s[a] = i;
        a = j;
    }
    assert(a == i);
    return a;
}


bool TriangleLib::compareEdge(edges_t a, edges_t b)
{
    return a.first < b.first;
}

