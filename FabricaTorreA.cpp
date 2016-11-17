#include "FabricaTorreA.h"
#include "Game.h"
#include "TorreA.h"

extern Game * game;

FabricaTorreA::FabricaTorreA() {// imagen de la fabrica
    setPixmap(QPixmap(":/images/intn.png"));
}

void FabricaTorreA::mousePressEvent(QGraphicsSceneMouseEvent* event){ // cambia el raton por la misma imagen
    if (!game->building){ // si a seleccionado una fabrica osea no es nulo
        game->building = new TorreA();
        game->setCursor(QString(":/images/intn.png")); //durante el movimiento tendra la imagen
    }
}
