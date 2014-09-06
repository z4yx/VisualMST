#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "resultdialog.h"
#include "algochoicedialog.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QDebug>

#include "algo/primalgorithm.h"
#include "algo/trianglelib.h"
#include "algo/algorithmworker.h"


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
    connect(mGraphManager, SIGNAL(itemDeleted(int)), mVertexes, SLOT(deleteVertex(int)));
    connect(mVertexes, SIGNAL(newVertexesLoaded(QMap<int,QPointF>)), mGraphManager, SLOT(drawEditableVertex(QMap<int,QPointF>)));
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
    if(currentAlgo & AlgoChoiceDialog::Delaunay){
        mAlgo = new TriangleLib();
        qDebug() << "start TriangleLib";
        mProgressDialog->setLabel(new QLabel("Calculating using triangle..."));
    }else if(currentAlgo & AlgoChoiceDialog::Prim){
        mAlgo = new PrimAlgorithm();
        qDebug() << "start PrimAlgorithm";
        mProgressDialog->setLabel(new QLabel("Calculating using prim..."));
    }else{
        qDebug() << "No algorithm specified";
        return;
    }

    connect(mAlgo, SIGNAL(progressUpdated(int)), mProgressDialog, SLOT(setValue(int)));

    qDebug() << "new thread";
    mThread = new AlgorithmWorker(mAlgo, &mVertexes->getVertexes());
    connect(mThread, SIGNAL(finished()), this, SLOT(calculationDone()));
    qDebug() << "Thread start";
    mThread->start();

    qDebug() << "dialog shown";
}

void MainWindow::preStartCalculation()
{

    mProgressDialog->reset();
    mProgressDialog->setModal(true);
    mProgressDialog->show();

    //Let other events process
    QCoreApplication::postEvent(this, new QEvent(QEvent::User));
//    startCalculation();
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
    AlgoChoiceDialog *dialog = new AlgoChoiceDialog(this);
    if(dialog->exec() != QDialog::Accepted){
        delete dialog;
        return;
    }
    currentAlgo = dialog->getAlgorithmChoices();
    if(currentAlgo == 0){
        delete dialog;
        return;
    }
    delete dialog;

    if(isCalculating)
        return;
    isCalculating = true;

    mResultDialog = new ResultDialog(this);
    mResultDialog->setModal(true);

    preStartCalculation();
}

void MainWindow::on_actionNewPoint_triggered()
{
    mNewPointDialog->setModal(true);
    if(mNewPointDialog->exec() == QDialog::Accepted){
        QPointF pt = mNewPointDialog->getInputPoint();
        addNewPoint(pt);
    }
}

void MainWindow::on_actionRemovePoint_triggered()
{
    mGraphManager->removeSelectedItem();
}

void MainWindow::calculationDone()
{
    QRectF rect;

    qDebug() << "done";
    mProgressDialog->cancel();

    if(currentAlgo & AlgoChoiceDialog::Delaunay){
        TriangleLib *algo = dynamic_cast<TriangleLib*> (mAlgo);
        currentAlgo ^= AlgoChoiceDialog::Delaunay;

        mResultDialog->setVoronoiEdges(algo->getVoronoiEdges(rect), rect);
        mResultDialog->setDelaunayEdges(algo->getDelaunayEdges());

    }else if(currentAlgo & AlgoChoiceDialog::Prim){
        PrimAlgorithm *algo = dynamic_cast<PrimAlgorithm*> (mAlgo);
        currentAlgo ^= AlgoChoiceDialog::Prim;

    }

    qDebug() << "delete";
    delete mThread;

    if(currentAlgo == 0){
        mResultDialog->setMSTEdges(mAlgo->getMSTEdges());
        delete mAlgo;

        mResultDialog->setMSTVertexes(mVertexes->getVertexes());
        mResultDialog->exec();
        delete mResultDialog;

        isCalculating = false;
    }else{
        delete mAlgo;
        preStartCalculation();
    }
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

