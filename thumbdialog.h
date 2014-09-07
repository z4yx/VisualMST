#ifndef THUMBDIALOG_H
#define THUMBDIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

class ThumbDialog : public QDialog
{
    Q_OBJECT

    QGraphicsView *mView;
    QGraphicsScene *mScene;
    QGraphicsRectItem *mMapRect;
    qreal mWidthFactor, mHeightFactor, mXOffset, mYOffset;
    QRectF mOrigSceneRect;
protected:
    void showEvent(QShowEvent * event);
public:
    ThumbDialog(QWidget * parent = 0, Qt::WindowFlags f = 0);
public slots:
    void setFullMapRect(QRectF rect);
    void setCurrentMapRect(QRectF rect);
};

#endif // THUMBDIALOG_H
