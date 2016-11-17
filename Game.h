#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include "Tower.h"


class Game: public QGraphicsView{
    Q_OBJECT
public:

    Game(); //constructor
    void setCursor(QString filename);  // cambia el curso (le pone imagen cuando selecciona el const)
    void mouseMoveEvent(QMouseEvent *event); //recibe el moviemiento del mouse y le sigue imagen si apreto
    void mousePressEvent(QMouseEvent *event); // recibe los click para poner torres
    void createEnemies(int numberOfEnemies); // crea enemigos
    void creaPista();// dibuja la pista

    QGraphicsScene * scene;
    QGraphicsPixmapItem * cursor; // imagen señalada
    Tower * building; // puntero a torre
    QTimer * TimerCrear; // timer
    int EnemigosCreados; // contador de enemigos
    int MaxEnem; // enemigos maximos para crear
    QList<QPointF> pointsToFollow; // lista de puntos del camino
public slots:
    // los slots son funciones que se usan en un connect para generar alguna accion
    void spawnEnemy(); // generar enemigos
};

#endif // GAME_H
