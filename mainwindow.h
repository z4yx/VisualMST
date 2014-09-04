#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressDialog>
#include "graphmanager.h"
#include "view.h"
#include "algo/abstructmstalgo.h"

namespace Ui {
class MainWindow;
}

class ResultDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_actionZoom_In_triggered();

    void on_actionZoom_Out_triggered();

    void on_actionOpen_triggered();

    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_actionClose_triggered();

    void on_actionSelectMode_triggered();

    void on_actionMoveMode_triggered();

    void on_actionFindMST_triggered();

public slots:
    void calculationDone();

private:
    bool confirmClose();
    void startCalculation();
    Ui::MainWindow *ui;
    QProgressDialog *mProgressDialog;
    ResultDialog *mResultDialog;
    MSTGraphicsView *mGraphicsView;
    GraphManager *mGraphManager;
    MSTVertexes *mVertexes;
    AbstructMSTAlgo *mAlgo;
    QThread *mThread;
};

#endif // MAINWINDOW_H
