#include "entity.h"
#include <cmath>

Entity::Entity(int tilePosX, int tilePosY)
    : m_thingsPixmap(":/images/things.png")
{
    m_tileX = tilePosX;
    m_tileY = tilePosY;
    m_screenPosX = tilePosX * 16 + 8.0f + 8.0f - 30/2;
    m_screenPosY = tilePosY * 16 + 8.0f - 20/2;
}

float Entity::getScreenPosX()
{
    return m_screenPosX;
}

float Entity::getScreenPosY()
{
    return m_screenPosY;
}

int Entity::getTileX()
{
    return m_tileX;
}

int Entity::getTileY()
{
    return m_tileY;
}

void Entity::move(float x, float y)
{
    m_screenPosX += x;
    m_screenPosY += y;

    if ((int)(m_screenPosX + 8 + 30/2) % 16 == 0 && (int)(m_screenPosY + 8 + 30/2) % 16 == 0)
    {
        m_tileX = (int) round((m_screenPosX - 8 + 30/2) / 16);
        m_tileY = (int) round((m_screenPosY - 8 + 30/2) / 16);
    }
}

void Entity::teleport(int x, int y)
{
    m_tileX = x;
    m_tileY = y;
    m_screenPosX = x * 16.0f + 8.0f - 30/2;
    m_screenPosY = y * 16.0f + 8.0f - 30/2;
}
