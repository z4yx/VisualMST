#include "algochoicedialog.h"
#include "ui_algochoicedialog.h"

AlgoChoiceDialog::AlgoChoiceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlgoChoiceDialog)
{
    ui->setupUi(this);
}

AlgoChoiceDialog::~AlgoChoiceDialog()
{
    delete ui;
}

AlgoChoiceDialog::AlgorithmEnum AlgoChoiceDialog::getAlgorithmChoices()
{
    int t = Nothing;
    if(ui->checkDelaunay->isChecked())
        t |= Delaunay;
    if(ui->checkPrim->isChecked())
        t |= Prim;
    return (AlgorithmEnum)t;
}
