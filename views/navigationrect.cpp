#include "navigationrect.h"
#include "window/thumbdialog.h"

#include <QPaintEvent>
#include <QDebug>

NavigationRect::NavigationRect(ThumbDialog *dialog, QGraphicsItem *parent) :
    mDialog(dialog),
    QGraphicsRectItem(parent)
{
}
void NavigationRect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsRectItem::mousePressEvent(event);
    mDialog->mapRectMove(true);
    qDebug() << "press";
}

void NavigationRect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsRectItem::mouseReleaseEvent(event);
    mDialog->mapRectMove(false);
    qDebug() << "release";
}


