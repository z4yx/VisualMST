#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "resultdialog.h"

#include <QFileDialog>
#include <QMessageBox>

#include "algo/primalgorithm.h"
#include "algo/trianglelib.h"
#include "algo/algorithmworker.h"

#define ALGO TriangleLib

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mProgressDialog = new QProgressDialog(this);
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

    mProgressDialog->reset();
    mProgressDialog->setModal(true);
    connect(mAlgo, SIGNAL(progressUpdated(int)), mProgressDialog, SLOT(setValue(int)));

    mThread = new AlgorithmWorker(mAlgo, mVertexes->getVertexes());
    connect(mThread, SIGNAL(finished()), this, SLOT(calculationDone()));
    mThread->start();

    mProgressDialog->show();
}

void MainWindow::on_actionNew_triggered()
{
    if(!confirmClose())
        return;
    mVertexes->clearVertexes();
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Vertex File", "/Users/zhang/tmp", "Vertex Files (*.vtx)");
    mVertexes->loadVertexesFromFile(fileName);
    mGraphManager->drawVertexes(mVertexes->getVertexes());
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
    mVertexes->clearVertexes();
}

void MainWindow::on_actionSelectMode_triggered()
{
    mGraphicsView->setPointerMode(MSTGraphicsView::SelectMode);
}

void MainWindow::on_actionMoveMode_triggered()
{
    mGraphicsView->setPointerMode(MSTGraphicsView::MoveMode);
}

void MainWindow::on_actionFindMST_triggered()
{
    startCalculation();
}

void MainWindow::calculationDone()
{
    ResultDialog dialog;
    QRectF rect;

    ALGO *algo = dynamic_cast<ALGO*> (mAlgo);

    mProgressDialog->cancel();

    dialog.setModal(true);
    dialog.setVoronoiEdges(algo->getVoronoiEdges(rect), rect);
    dialog.setMSTVertexes(mVertexes->getVertexes());
    dialog.setDelaunayEdges(algo->getDelaunayEdges());
    dialog.setMSTEdges(algo->getMSTEdges());

    delete mThread;
    delete mAlgo;

    dialog.exec();
}
