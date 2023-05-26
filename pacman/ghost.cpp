#include "ghost.h"
#include <QTimer>

Ghost::Ghost(const QString &sprite_path, int _type, int x, int y, int speed, int initialMove, QGraphicsItem *parent): QGraphicsItem(parent)
{
    type = _type;
    posx=x;
    posy=y;
    velocidad=speed;
    colides = false;
    currentMove = initialMove;

    setPos(posx,posy);
    sprite = QPixmap(sprite_path);
}


int Ghost::getPosx() const
{
    return posx;
}

void Ghost::setPosx(int newPosx)
{
    posx = newPosx;
}

int Ghost::getPosy() const
{
    return posy;
}

void Ghost::setPosy(int newPosy)
{
    posy = newPosy;
}

int Ghost::getVelocidad() const
{
    return velocidad;
}

void Ghost::setVelocidad(int newVelocidad)
{
    velocidad = newVelocidad;
}

int Ghost::getType() const
{
    return type;
}

void Ghost::setType(int newType)
{
    type = newType;
}

void Ghost::MoveUp()
{
    posy-=velocidad;
    setPos(posx,posy);
}

void Ghost::MoveDown()
{
    posy+=velocidad;
    setPos(posx,posy);
}

void Ghost::MoveLeft()
{
    posx-=velocidad;
    setPos(posx,posy);
}

void Ghost::MoveRight()
{
    posx+=velocidad;
    if (posx == 431 && posy == 270) {
        setPos(-posx,posy);
    } else {
        setPos(posx,posy);
    }
}

void Ghost::moveGhost()
{
    MoveRight();
}

const vector<int> &Ghost::getMovement() const
{
    return movement;
}

void Ghost::setMovement(const vector<int> &newMovement)
{
    movement = newMovement;
}

void Ghost::saveMovement(int n)
{
    movement.push_back(n);
}

bool Ghost::getColides() const
{
    return colides;
}

void Ghost::setColides(bool newColides)
{
    colides = newColides;
}

int Ghost::getCurrentMove() const
{
    return currentMove;
}

void Ghost::setCurrentMove(int newCurrentMove)
{
    currentMove = newCurrentMove;
}

QRectF Ghost::boundingRect() const
{
    return QRectF(0,0,20,20);
}

QPainterPath Ghost::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Ghost::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite.copy(30,30*type,30,30).scaled(20, 20, Qt::KeepAspectRatio));
}
