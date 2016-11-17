#include "Tower.h"
#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include "Bullet.h"
#include <QPointF>
#include <QLineF>
#include "Game.h"
#include <QTimer>
#include <QGraphicsRectItem>
#include "Enemy.h"

extern Game * game;

#include <QDebug>
Tower::Tower():QObject(){
    // crea un vector de puntos
    QVector<QPointF> points;
    points << QPoint(1,0) << QPoint(2,0) << QPoint(3,1) << QPoint(3,2) << QPoint(2,3)
               << QPoint(1,3) << QPoint(0,2) << QPoint(0,1);


    int ESCALA = 70; // escala del octagono

    for (size_t i = 0, n = points.size(); i < n; i++){ // todos los multiplica por el factor
        points[i] *= ESCALA;
    }

    // crea un poligono con precision punto flotante y lo pasa como parametro para q sea un item
    attack_area = new QGraphicsPolygonItem(QPolygonF(points),this);

    //pinta el Octagono creado
    attack_area->setPen(QPen(Qt::DotLine));

    // movimiento del Poligono
    QPointF poly_centro(1.5,1.5); // establece el centro del poligono
    poly_centro *= ESCALA; // lo multiplica por el factor de crecimiento

    //centro del poligono
    poly_centro = mapToScene(poly_centro);;


    QPointF cent_torre(x()+40,y()+40); // el centro de la torre es x() pero al real se le aumenta el tamaño de la imagen
    QLineF ln(poly_centro,cent_torre); //linea del centro del poligono hasta donde esta la torre
    attack_area->setPos(x()+ln.dx(),y()+ln.dy());
    // lo jala al polygono hasta la torre, dx() devuelve la distancia horizontal y dy la vertical
    //mas la posicion de la torre
    // se suma por q recordamos q el 0,0 esta en la esquina sup izq


    // el punto de ataque en 0,0 al comienzo
    attack_dest = QPointF(0,0);
    // al comienzo no tiene enemigos en su rango
    con_objetivo = false;
}

double Tower::distanceTo(QGraphicsItem *item){

    QLineF ln(this->pos(),item->pos()); // se crea una linea entre la torre y el item pasado como parametro
    return ln.length(); // distancia entre ambos
}

void Tower::fire(){
    Bullet * bullet = new Bullet(); // crea objeto bala
    bullet->setPos(x()+40,y()+40); // comienza en el centro de la torre

    QLineF ln(QPointF(x()+44,y()+44),attack_dest); // se crea una linea desde el centro de la torre hasta el enemigo
    int angle = -1 * ln.angle(); // se halla el angulo donde esta el objetivo

    bullet->setRotation(angle); // voltea la imagen de la bala
    game->scene->addItem(bullet); // se agrega a la escena la bala
}

void Tower::obt_objetivo(){


    // lista de elementos q chocan con el polygono de ataque
    QList<QGraphicsItem *> colliding_items = attack_area->collidingItems();

    // no hay objetivo por ahora
    con_objetivo = false;

    // encuentra al enemigo
    double mas_cerca = 300;
    QPointF punto_cerca(0,0);
    //recorre toda la lista
    for (int i = 0, n = colliding_items.size(); i < n; ++i){

        // verifica q sea un enemigo
        Enemy * enemy = dynamic_cast<Enemy *>(colliding_items[i]);

        // comparar distacias
        if (enemy){ //si existe un enemigo
            double esta_dist = distanceTo(colliding_items[i]); //distacia al enemigo
            if (esta_dist < mas_cerca){ //si la distancia es menor a la q tengo
                mas_cerca = esta_dist; //remplazo
                punto_cerca = colliding_items[i]->pos(); // la posicion del enemigo mas cercano
                con_objetivo = true; //y si encontre objetivo
            }
        }
    }

    // si hay un enemigo , lo ataca
    if (con_objetivo){
        attack_dest = punto_cerca; // punto de ataque es el pnto mas cercano
        fire();// dispara
    }
}
