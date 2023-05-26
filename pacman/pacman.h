#ifndef PACMAN_H
#define PACMAN_H

#include <QGraphicsItem>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QObject>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

class Pacman: public QObject, public QGraphicsItem
{
    Q_OBJECT

    int radio;
    int posx;
    int posy;
    int velocidad;

public:
    Pacman(const QString &sprite_path, QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;

    //Movimiento
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();


    int getPosx() const;
    void setPosx(int value);
    int getPosy() const;
    void setPosy(int value);
    int getRadio() const;
    void setRadio(int value);

    int getSprite_position() const;
    void setSprite_position(int newSprite_position);

    int getSprite_end() const;
    void setSprite_end(int newSprite_end);

private:
    QPixmap sprite;
    QTimer* timer;
    int sprite_position;
    int sprite_end;
};


#endif // PACMAN_H
