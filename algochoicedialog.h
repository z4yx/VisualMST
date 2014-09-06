#ifndef ALGOCHOICEDIALOG_H
#define ALGOCHOICEDIALOG_H

#include <QDialog>

namespace Ui {
class AlgoChoiceDialog;
}

class AlgoChoiceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlgoChoiceDialog(QWidget *parent = 0);
    ~AlgoChoiceDialog();
    enum AlgorithmEnum{
        Nothing,
        Prim = 1, Delaunay = 2
    };
    AlgorithmEnum getAlgorithmChoices();

private:
    Ui::AlgoChoiceDialog *ui;
};

#endif // ALGOCHOICEDIALOG_H
