#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressDialog>
#include "controller/graphmanager.h"
#include "views/view.h"
#include "algo/abstructmstalgo.h"
#include "newpointdialog.h"
#include "thumbdialog.h"

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

    void on_actionPointMode_triggered();

    void on_actionNewPoint_triggered();

    void on_actionRemovePoint_triggered();

    void on_actionNavigation_triggered();

    void on_actionNavigation_toggled(bool arg1);

public slots:
    void calculationDone();
    void addNewPoint(QPointF pt);
    void navigationClosed();

protected:
    bool event(QEvent *event);

private:
    bool confirmClose();
    void startCalculation();
    void preStartCalculation();
    Ui::MainWindow *ui;
    QProgressDialog *mProgressDialog;
    NewPointDialog *mNewPointDialog;
    ResultDialog *mResultDialog;
    ThumbDialog *mThumbDialog;
    MSTGraphicsView *mGraphicsView;
    GraphManager *mGraphManager;
    MSTVertexes *mVertexes;
    AbstructMSTAlgo *mAlgo;
    QThread *mThread;

    bool isCalculating;
    int currentAlgo;
};

#endif // MAINWINDOW_H
