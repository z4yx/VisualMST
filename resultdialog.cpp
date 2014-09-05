#include "resultdialog.h"
#include "ui_resultdialog.h"

ResultDialog::ResultDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultDialog)
{
    ui->setupUi(this);

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

void ResultDialog::setMSTVertexes(const QList<QPointF> &vtx)
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
