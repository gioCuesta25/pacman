#ifndef INKY_H
#define INKY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPropertyAnimation>
#include "fantasma.h"

class Inky : public QObject, public QGraphicsPixmapItem, public Fantasma
{
    Q_OBJECT
    Q_PROPERTY(qreal weak READ weak WRITE setWeak)
public:
    explicit Inky();

    void startWeakMode();
    void stopWeakMode();
    bool isWeak();
signals:

private slots:
    void updatePixmap();
    void setWeak(qreal val);
private:
    qreal weak() const;

    QTimer m_timer;
    int m_currentIndex;
    QPixmap m_upPixmap, m_rightPixmap, m_downPixmap, m_leftPixmap;
    QPixmap m_weakPixmap;
    QPropertyAnimation *m_weakAnim;
    qreal m_weak;
    constexpr static int ANIM_SPEED = 125;

    void loadPixmap();
};
#endif // INKY_H
