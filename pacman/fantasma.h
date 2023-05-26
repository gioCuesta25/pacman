#ifndef FANTASMA_H
#define FANTASMA_H

#include <QPixmap>
#include "entity.h"

class Fantasma: public Entity
{
public:
public:
    Fantasma(int tilePosX, int tilePosY, int destinationX, int destinationY);

    void setDestination(int x, int y);
    int getDestX();
    int getDestY();

    void setDirection(int dir);
    int getDirection();
    void move();

    bool isScattering();
    void setScattering(bool s);

    bool isOutOfCage();

    bool shouldTakeDecision();
    void setTakeDecision(bool d);

    void teleport(int x, int y);


    bool isAnimated() const;
    void setAnimated(bool val);
protected:
    int m_destinationTileX;
    int m_destinationTileY;
    int m_moving;

    bool m_scattering;
    bool m_outOfCage;

    bool m_decision;

    int m_frightened;

    QPixmap m_frightenedPixmap;

    bool m_isAnimated;

    const int WEAK_MODE_SPEED;

    float m_speed;
};


#endif // FANTASMA_H
