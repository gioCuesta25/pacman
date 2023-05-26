#include "pacman.h"
#include <QTimer>

Pacman::Pacman(const QString &sprite_path, QGraphicsItem *parent): QGraphicsItem(parent)
{
    radio=15;
    posx=200;
    posy=320;
    velocidad=3;
    sprite_position = 2;
    sprite_end = 0;
    setPos(posx,posy);

    sprite = QPixmap(sprite_path);
}

int Pacman::getPosx() const
{
    return posx;
}

void Pacman::setPosx(int value)
{
    posx = value;
}

int Pacman::getPosy() const
{
    return posy;
}

void Pacman::setPosy(int value)
{
    posy = value;
}

int Pacman::getSprite_position() const
{
    return sprite_position;
}

void Pacman::setSprite_position(int newSprite_position)
{
    sprite_position = newSprite_position;
}

int Pacman::getSprite_end() const
{
    return sprite_end;
}

void Pacman::setSprite_end(int newSprite_end)
{
    sprite_end = newSprite_end;
}

QRectF Pacman::boundingRect() const
{
    return QRectF(0,0,20,20);
}

QPainterPath Pacman::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Pacman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite.copy((90*sprite_position)+sprite_end,0,30,30).scaled(20, 20, Qt::KeepAspectRatio));
}

void Pacman::MoveUp()
{
    posy-=velocidad;
    setPos(posx,posy);
}

void Pacman::MoveDown()
{
    posy+=velocidad;
    setPos(posx,posy);
}

void Pacman::MoveLeft()
{
    posx-=velocidad;
    setPos(posx,posy);
}

void Pacman::MoveRight()
{
    posx+=velocidad;
    if (posx == 431 && posy == 270) {
        setPos(-posx,posy);
    } else {
        setPos(posx,posy);
    }
}

