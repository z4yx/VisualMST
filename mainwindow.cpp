#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "resultdialog.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

#include "algo/primalgorithm.h"
#include "algo/trianglelib.h"
#include "algo/algorithmworker.h"

#define ALGO TriangleLib

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    isCalculating(false)
{
    ui->setupUi(this);

    mProgressDialog = new QProgressDialog(this);
    mNewPointDialog = new NewPointDialog(this);
    mResultDialog = new ResultDialog(this);

    mGraphicsView = new MSTGraphicsView(this);
    mGraphicsView->initView();
    ui->gridLayout->addWidget(mGraphicsView, 0, 0, 1, 1);

    QActionGroup *grp = new QActionGroup(this);
    grp->addAction(ui->actionSelectMode);
    grp->addAction(ui->actionMoveMode);
    grp->addAction(ui->actionPointMode);
    ui->actionSelectMode->setChecked(true);

    mVertexes = new MSTVertexes();

    mGraphManager = new GraphManager(mGraphicsView);

    connect(mGraphicsView, SIGNAL(newPointEvent(QPointF)), this, SLOT(addNewPoint(QPointF)));
    connect(mGraphManager, SIGNAL(itemPosChangedEvent(int,QPointF)), mVertexes, SLOT(changeVertexPos(int,QPointF)));
    connect(mVertexes, SIGNAL(newVertexesLoaded(QList<QPointF>)), mGraphManager, SLOT(drawEditableVertex(QList<QPointF>)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mGraphManager;
    delete mVertexes;
}


void MainWindow::on_actionZoom_In_triggered()
{
    mGraphicsView->zoomIn(0.05);
}

void MainWindow::on_actionZoom_Out_triggered()
{
    mGraphicsView->zoomOut(0.05);
}

bool MainWindow::confirmClose()
{
    if(mVertexes->isChanged()){
        QMessageBox msgBox;
        msgBox.setText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch(ret){

        case QMessageBox::Save:
            on_actionSave_triggered();
            break;
        case QMessageBox::Discard:

            break;
        case QMessageBox::Cancel:
            return false;
            break;
        }
    }
    return true;
}

void MainWindow::startCalculation()
{
    mAlgo = new ALGO();

    connect(mAlgo, SIGNAL(progressUpdated(int)), mProgressDialog, SLOT(setValue(int)));

    qDebug() << "new thread";
    mThread = new AlgorithmWorker(mAlgo, &mVertexes->getVertexes());
    connect(mThread, SIGNAL(finished()), this, SLOT(calculationDone()));
    qDebug() << "Thread start";
    mThread->start();

    qDebug() << "dialog shown";
}

void MainWindow::on_actionNew_triggered()
{
    if(!confirmClose())
        return;
    mVertexes->clearDocuments();
}

void MainWindow::on_actionOpen_triggered()
{
    if(!confirmClose())
        return;
    QString fileName = QFileDialog::getOpenFileName(this, "Open Vertex File", "/Users/zhang/tmp", "Vertex Files (*.vtx)");
    mVertexes->loadVertexesFromFile(fileName);
    qDebug() << "Open Done!";
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Vertex File", "", "Vertex Files (*.vtx)");
    mVertexes->saveVertexesToFile(fileName);
}

void MainWindow::on_actionClose_triggered()
{
    if(!confirmClose())
        return;
    mVertexes->clearDocuments();
    close();
}

void MainWindow::on_actionSelectMode_triggered()
{
    mGraphicsView->setPointerMode(MSTGraphicsView::SelectMode);
}

void MainWindow::on_actionMoveMode_triggered()
{
    mGraphicsView->setPointerMode(MSTGraphicsView::MoveMode);
}

void MainWindow::on_actionPointMode_triggered()
{
    mGraphicsView->setPointerMode(MSTGraphicsView::DrawPointMode);
}

void MainWindow::on_actionFindMST_triggered()
{
    if(isCalculating)
        return;
    isCalculating = true;


    mProgressDialog->reset();
    mProgressDialog->setModal(true);
    mProgressDialog->show();
    QCoreApplication::postEvent(this, new QEvent(QEvent::User));
//    startCalculation();
}

void MainWindow::on_actionNewPoint_triggered()
{
    mNewPointDialog->setModal(true);
    if(mNewPointDialog->exec() == QDialog::Accepted){
        QPointF pt = mNewPointDialog->getInputPoint();
        addNewPoint(pt);
    }
}

void MainWindow::calculationDone()
{
    ResultDialog dialog;
    QRectF rect;

    ALGO *algo = dynamic_cast<ALGO*> (mAlgo);

    qDebug() << "done";
    mProgressDialog->cancel();

    dialog.setModal(true);
    dialog.setVoronoiEdges(algo->getVoronoiEdges(rect), rect);
    dialog.setMSTVertexes(mVertexes->getVertexes());
    dialog.setDelaunayEdges(algo->getDelaunayEdges());
    dialog.setMSTEdges(algo->getMSTEdges());

    qDebug() << "delete";
    delete mThread;
    delete mAlgo;

    dialog.exec();
    isCalculating = false;
}

void MainWindow::addNewPoint(QPointF pt)
{
    int idx;
    mVertexes->newVertex(idx, pt);
    mGraphManager->drawSingleVertex(pt, idx);
    qDebug() << "new point id" << idx;
}

bool MainWindow::event(QEvent *event)
{
    if(event->type() == QEvent::User){
        qDebug() << "event";
        startCalculation();
        return true;
    }
    return QMainWindow::event(event);
}

