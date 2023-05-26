#include "fantasma.h"
#include "entity.h"

Fantasma::Fantasma(int tilePosX, int tilePosY, int destinationX, int destinationY)
    : Entity(tilePosX, tilePosY), m_scattering(true), m_outOfCage(false),
      m_decision(true), m_frightened(false), WEAK_MODE_SPEED(4000)
{
    setDestination(destinationX, destinationY);
    setDirection(0);
    m_frightenedPixmap = m_thingsPixmap.copy(240, 30, 30*2, 30);
}

void Fantasma::setDestination(int x, int y)
{
    m_destinationTileX = x;
    m_destinationTileY = y;
}

int Fantasma::getDestX()
{
    return m_destinationTileX;
}

int Fantasma::getDestY()
{
    return m_destinationTileY;
}

void Fantasma::setDirection(int dir)
{
    m_moving = dir;
}

int Fantasma::getDirection()
{
    return m_moving;
}

void Fantasma::move()
{
    switch (m_moving)
    {
    case 1:
        Entity::move(0, -m_speed);
        break;
    case -1:
        Entity::move(0, m_speed);
        break;
    case 2:
        Entity::move(-m_speed, 0);
        break;
    case -2:
        Entity::move(m_speed, 0);
        break;
    }
}

bool Fantasma::isScattering()
{
    return m_scattering;
}

void Fantasma::setScattering(bool s)
{
    m_scattering = s;
}

bool Fantasma::isOutOfCage()
{
    return m_outOfCage;
}

bool Fantasma::shouldTakeDecision()
{
    return m_decision;
}

void Fantasma::setTakeDecision(bool d)
{
    m_decision = d;
}

void Fantasma::teleport(int x, int y)
{
    Entity::teleport(x, y);
    m_outOfCage = true;
}


bool Fantasma::isAnimated() const
{
    return m_isAnimated;
}

void Fantasma::setAnimated(bool val)
{
    m_isAnimated = val;
}
