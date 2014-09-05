#include "newpointdialog.h"
#include "ui_newpointdialog.h"

NewPointDialog::NewPointDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPointDialog)
{
    ui->setupUi(this);


    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

NewPointDialog::~NewPointDialog()
{
    delete ui;
}

QPointF NewPointDialog::getInputPoint()
{
    qreal x = ui->edit_x->value();
    qreal y = ui->edit_y->value();

    return QPointF(x, y);
}
