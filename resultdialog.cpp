#include "resultdialog.h"
#include "ui_resultdialog.h"

ResultDialog::ResultDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultDialog)
{
    ui->setupUi(this);

    ui->label_delaunay->setVisible(false);
    ui->label_prime->setVisible(false);

    mGraphicsView = new MSTGraphicsView(this);
    mGraphicsView->initView();
    mGraphicsView->setPointerMode(MSTGraphicsView::MoveMode);
    ui->verticalLayout->addWidget(mGraphicsView);

    mGraphManager = new GraphManager(mGraphicsView);
}

ResultDialog::~ResultDialog()
{
    delete ui;
    delete mGraphManager;
}

void ResultDialog::setMSTVertexes(const QMap<int,QPointF> &vtx)
{
    mGraphManager->drawVertexes(vtx);
    if(vtx.size() < 500)
        mGraphicsView->setRenderHint(QPainter::Antialiasing);
}

void ResultDialog::setMSTEdges(const QList<QLineF> &e)
{
    mGraphManager->drawMSTEdges(e, true);
}

void ResultDialog::setDelaunayEdges(const QList<QLineF> &e)
{
    mGraphManager->drawDelaunayEdges(e, false);
}

void ResultDialog::setVoronoiEdges(const QList<QLineF> &e, const QRectF &border)
{
    mGraphManager->drawVoronoiEdges(e, border, false);
}

void ResultDialog::setPrimTimeUsage(qint64 t)
{
    ui->label_prime->setText(QString("Prim used %1 ms").arg(t));
    ui->label_prime->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    ui->label_prime->setVisible(true);
}

void ResultDialog::setDelaunayTimeUsage(qint64 t)
{
    ui->label_delaunay->setText(QString("Delaunay used %1 ms").arg(t));
    ui->label_delaunay->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    ui->label_delaunay->setVisible(true);
}

void ResultDialog::on_showMST_clicked(bool checked)
{
    mGraphManager->showMSTEdges(checked);
}

void ResultDialog::on_showDelaunay_clicked(bool checked)
{
    mGraphManager->showDelaunayEdges(checked);
}

void ResultDialog::on_showVoronoi_clicked(bool checked)
{
    mGraphManager->showVoronoiEdges(checked);
}
