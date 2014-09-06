#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QDialog>
#include "graphmanager.h"
#include "view.h"

namespace Ui {
class ResultDialog;
}

class ResultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResultDialog(QWidget *parent = 0);
    ~ResultDialog();

    void setMSTVertexes(const QMap<int,QPointF>&);
    void setMSTEdges(const QList<QLineF>&);
    void setDelaunayEdges(const QList<QLineF>&);
    void setVoronoiEdges(const QList<QLineF>&, const QRectF &border);

    void setPrimTimeUsage(qint64 t);
    void setDelaunayTimeUsage(qint64 t);
private slots:
    void on_showMST_clicked(bool checked);

    void on_showDelaunay_clicked(bool checked);

    void on_showVoronoi_clicked(bool checked);

private:
    Ui::ResultDialog *ui;
    MSTGraphicsView *mGraphicsView;
    GraphManager *mGraphManager;
};

#endif // RESULTDIALOG_H
