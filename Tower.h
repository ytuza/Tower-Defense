#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QPointF>
#include <QObject>

class Tower:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Tower(); // constructor
    double distanceTo(QGraphicsItem * item);
    virtual void fire(); // virtual para ser definida por las clases hijas

public slots:
    void obt_objetivo();
protected:
    QGraphicsPolygonItem * attack_area; // poligono de ataque
    QPointF attack_dest; //punto al que atacara
    bool con_objetivo; // tiene un objetivo o no ??
};

#endif // TOWER_H
