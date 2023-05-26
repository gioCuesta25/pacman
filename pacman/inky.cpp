#include "inky.h"


void Inky::loadPixmap()
{
    m_upPixmap = m_thingsPixmap.copy(0, 90, 2*30, 30);
    m_rightPixmap = m_thingsPixmap.copy(180, 90, 2*30, 30);
    m_downPixmap = m_thingsPixmap.copy(60, 90, 2*30, 30);
    m_leftPixmap = m_thingsPixmap.copy(120, 90, 2*30, 30);
}

Inky::Inky()
    : Fantasma(11, 17, 26, 32), m_currentIndex(0), m_weak(0)
{
    m_speed = 0.75f;

    setPixmap(m_thingsPixmap.copy(60,90, 30, 30));
    loadPixmap();

    setTransformOriginPoint(30, 30);
    connect(&m_timer, &QTimer::timeout, this, &Inky::updatePixmap);
    m_timer.start(ANIM_SPEED);

    m_weakAnim = new QPropertyAnimation(this, "weak", this);
    m_weakAnim->setStartValue(WEAK_MODE_SPEED);
    m_weakAnim->setDuration(WEAK_MODE_SPEED);
    m_weakAnim->setEndValue(0);

}

void Inky::startWeakMode()
{
    m_weakAnim->start();
}

void Inky::stopWeakMode()
{
    m_weakAnim->stop();
    m_weak = 0;
}

void Inky::updatePixmap()
{
    if(getDirection() == 0 || !m_isAnimated)
    {
        setPixmap(m_thingsPixmap.copy(60,90, 30, 30));
        return;
    }

    if(!isWeak())
    {
        if(getDirection() == 1)
        {
            setPixmap(m_upPixmap.copy(m_currentIndex*30, 0, 30, 30));
        }
        else if(getDirection() == -2)
        {
            setPixmap(m_rightPixmap.copy(m_currentIndex*30, 0, 30, 30));
        }
        else if(getDirection() == -1)
        {
            setPixmap(m_downPixmap.copy(m_currentIndex*30, 0, 30, 30));
        }
        else if(getDirection() == 2)
        {
            setPixmap(m_leftPixmap.copy(m_currentIndex*30, 0, 30, 30));
        }
    }
    else
    {
        setPixmap(m_frightenedPixmap.copy(m_currentIndex*30, 0, 30, 30));
    }


    m_currentIndex += 1;
    m_currentIndex %= 2;

}

void Inky::setWeak(qreal val)
{
    m_weak = val;
}

qreal Inky::weak() const
{
    return m_weak;
}

bool Inky::isWeak()
{
    return m_weak > 0;
}
