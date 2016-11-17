
#ifndef TORREA_H
#define TORREA_H

#include "Tower.h"

class TorreA: public Tower{
    Q_OBJECT
public:
    TorreA();

public slots:

    void obt_objetivo();
};

#endif // TORREA_H

