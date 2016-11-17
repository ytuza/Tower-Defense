#include "Bullet.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h> // qSin, qCos, qTan
#include "Game.h"

extern Game * game;

Bullet::Bullet(): QObject(){

    setPixmap(QPixmap(":/images/bal.png")); // el mapa de bits sera de una imagen


    QTimer * move_timer = new QTimer(this); // incializo un timer
    //cada 50 se movera
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move()));
    //concectado al slot de movimiento de la bala

    move_timer->start(50);

    // inicializa rango maximo y distancia recorrida
    maxRange = 100;
    DistRec = 0;
}

void Bullet::move(){
    int tam_paso = 30; // tamaño del paso de la bala
    double theta = rotation();  //consigue el angulo a la q se dirige la bala con la rotacion de la imagen

    double dy = tam_paso * qSin(qDegreesToRadians(theta)); // seno del angulo por el paso para hallar loq avanzara en y
    double dx = tam_paso * qCos(qDegreesToRadians(theta));//coseno del angulo por el paso para hallar loq avanzara en x

    setPos(x()+dx, y()+dy); // cambia la posicion
}

double Bullet::getMaxRange(){
    return maxRange;
}

double Bullet::getDistRec(){
    return DistRec;
}

void Bullet::rango_alc(double rng){
maxRange = rng;
}

void Bullet::setDistRec(double dist){
    DistRec = dist;
}
