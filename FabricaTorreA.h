#ifndef FABRICATORREA_H
#define FABRICATORREA_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class FabricaTorreA: public QGraphicsPixmapItem{
public:
    FabricaTorreA();
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
};

#endif // FABRICATORREA_H


