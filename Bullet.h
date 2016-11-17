#ifndef BULLET_H
 #define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Bullet: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bullet();
public slots:
    void move(); //movimiento

    //getter de distancia maxima y recorrida
    double getMaxRange();
    double getDistRec();
    void rango_alc(double rng); // alcance
    void setDistRec(double dist); //distancia recorrida
private:
    double maxRange;
    double DistRec;
};

#endif // BULLET_H
