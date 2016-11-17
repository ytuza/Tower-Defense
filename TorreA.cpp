#include "TorreA.h"
#include <QTimer>
#include "Bullet.h"
#include "Game.h"

extern Game * game;

TorreA::TorreA(){
    // conecta el timer para que busq objetivos
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(obt_objetivo()));
    timer->start(1000);
}

//hereda el obtener objetivo
void TorreA::obt_objetivo(){
    Tower::obt_objetivo();
}
