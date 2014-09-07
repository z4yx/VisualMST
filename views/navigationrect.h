#ifndef NAVIGATIONRECT_H
#define NAVIGATIONRECT_H

#include <QGraphicsRectItem>

class ThumbDialog;

class NavigationRect : public QGraphicsRectItem
{
public:
    explicit NavigationRect(ThumbDialog *dialog, QGraphicsItem *parent = 0);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
private:
    ThumbDialog *mDialog;

};

#endif // NAVIGATIONRECT_H
