#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphmanager.h"
#include "view.h"

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

private:
    bool confirmClose();
    Ui::MainWindow *ui;
    ResultDialog *mResultDialog;
    MSTGraphicsView *mGraphicsView;
    GraphManager *mGraphManager;
    MSTVertexes *mVertexes;
};

#endif // MAINWINDOW_H
