#ifndef NEWPOINTDIALOG_H
#define NEWPOINTDIALOG_H

#include <QDialog>

namespace Ui {
class NewPointDialog;
}

class NewPointDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewPointDialog(QWidget *parent = 0);
    ~NewPointDialog();

    QPointF getInputPoint();

private:
    Ui::NewPointDialog *ui;
};

#endif // NEWPOINTDIALOG_H
