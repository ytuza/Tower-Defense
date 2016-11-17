#include "Game.h"
#include <QGraphicsScene>
#include "TorreA.h"
#include "Bullet.h"
#include "Enemy.h"
#include "FabricaTorreA.h"

#include <QTimer>
#include <QGraphicsLineItem>
#include <QPen>
#include <QGraphicsLineItem>
#include <QDebug>
#include<typeinfo>

Game::Game(): QGraphicsView(){

    scene = new QGraphicsScene(this); // crea una escena
    scene->setSceneRect(0,0,800,600); // establece el tamaño

    // realiza los cambios en la escena
    setScene(scene);

    // inicializa los cursores
    cursor = nullptr;
    building = nullptr;
    setMouseTracking(true);

    // alter window
    setFixedSize(800,600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // elimina las barras horizontal y vertical
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    TimerCrear = new QTimer(this); // timer para crear enemigos
    EnemigosCreados = 0; // enemigos creados
    MaxEnem = 0; // maximo de enemigos creados
    //creo los puntos para el camino
    pointsToFollow << QPointF(700,0) << QPointF(700,100) << QPointF(300,100) << QPointF(300,250) << QPointF(700,250) << QPointF(700,400)<< QPointF(300,400) << QPointF(0,600);

    createEnemies(4); // creo los elementos (Funcion declarada abajo)

    // creo el camino (funcion abajo)
    creaPista();

    // Creo los constructores
    FabricaTorreA * bt = new FabricaTorreA();


    //lso agrego a la escena
    scene->addItem(bt);



}

void Game::setCursor(QString filename){
    //funcion para que cuando haga click el cursor tenga el icono apretado
    //de parametro pasa un string con la direccion de la imagen

    if (cursor){ // elimina un cursor si lo hubiera
        scene->removeItem(cursor);
        delete cursor;
    }
    //crea un objeto mapa de bits y le define la imagen pasadotcomo parametro(la direccion)
    cursor = new QGraphicsPixmapItem();
    cursor->setPixmap(QPixmap(filename));
    scene->addItem(cursor); // la agrega a la escena
}

void Game::mouseMoveEvent(QMouseEvent *event){ // Moviemiento del cursor
    if (cursor){ // si el cursor tiene una imagen
        cursor->setPos(event->pos()); // debera seguir el cursor
    }
}

void Game::mousePressEvent(QMouseEvent *event){

    if (building){ // si no es nulo el puntero a torre (si a presionado un constructor)
        // crea una lista con las colisiones
        QList<QGraphicsItem *> items = cursor->collidingItems();

        //revisa si no choca con nada , si lo hace no realiza nada y sale de la funcion
        if (items.size() != 0 ){
            //qDebug() << "entro";
            return;
        }

        //qDebug() << "salio" << items.size() ;
        // si no crea un objeto torre
        scene->addItem(building);
        building->setPos(event->pos()); // cambia la posicion de la torre a la del teclado
        cursor = nullptr; // cursor vuelve a ser nulo no tiene imagen
        building = nullptr; // el puntero a torre apunta al vacio
    }
    else {
        QGraphicsView::mousePressEvent(event); // si no es un constructor seguira esperando
    }

}

void Game::createEnemies(int numberOfEnemies){
    EnemigosCreados = 0;
    MaxEnem = numberOfEnemies; // el numero maximo de enemigos es el parametro
    // lo conecta con un timer
    connect(TimerCrear,SIGNAL(timeout()),this,SLOT(spawnEnemy()));
    TimerCrear->start(1000);
}

void Game::creaPista(){ //creo la pista
    for (size_t i = 0, n = pointsToFollow.size()-1; i < n; i++){
        //crea lineas con cada dos puntos del array
        QLineF line(pointsToFollow[i],pointsToFollow[i+1]);
        QGraphicsLineItem * lineItem = new QGraphicsLineItem(line);
        //DIBUJA la linea
        QPen pen;
        pen.setWidth(15);
        pen.setColor(Qt::green);

        lineItem->setPen(pen);
        scene->addItem(lineItem);

    }
}

void Game::spawnEnemy(){
    // crea un enemigo
    Enemy * enemy = new Enemy(pointsToFollow); // crea un enemigo y le pasa como parametro la lista de puntos a seguir
    enemy->setPos(pointsToFollow[0]); // inicializa el enemigo en el primer punto
    scene->addItem(enemy); // agrega a la escena el enemigo
    EnemigosCreados += 1; // aumenta uno a enemigos creados

    if (EnemigosCreados >= MaxEnem){ // si la cantidad de enemigos creados es igual a la cant maxima
        TimerCrear->disconnect(); // desconectara el timer
    }
}
