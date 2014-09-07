#ifndef THUMBDIALOG_H
#define THUMBDIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

class NavigationRect;

class ThumbDialog : public QDialog
{
    Q_OBJECT

    bool rectMoving;
    QGraphicsView *mView;
    QGraphicsScene *mScene;
    NavigationRect *mMapRect;
    qreal mWidthFactor, mHeightFactor, mXOffset, mYOffset;
    QRectF mOrigSceneRect;
protected:
    void showEvent(QShowEvent * event);
//    void mousePressEvent(QMouseEvent * event);
//    void mouseReleaseEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent * event);
public:
    ThumbDialog(QWidget * parent = 0, Qt::WindowFlags f = 0);
    void mapRectMove(bool);
public slots:
    void setFullMapRect(QRectF rect);
    void setCurrentMapRect(QRectF rect);
signals:
    void navChanged(QRectF rect);
};

#endif // THUMBDIALOG_H
