#ifndef GHOST_H
#define GHOST_H

#include <iostream>
#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QWidget>
#include <QStyleOptionGraphicsItem>
#include <QPixmap>
#include <vector>

using namespace std;

class Ghost: public QObject, public QGraphicsItem
{
    Q_OBJECT

    int posx;
    int posy;
    int velocidad;
    int type;
    vector<int> movement;
    bool colides;
    int currentMove;


public:
    Ghost(const QString &sprite_path, int _type, int x, int y, int speed, int initialMove,QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;

    int getPosx() const;
    void setPosx(int newPosx);

    int getPosy() const;
    void setPosy(int newPosy);

    int getVelocidad() const;
    void setVelocidad(int newVelocidad);

    int getType() const;
    void setType(int newType);

    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();

    int *getMovements() const;
    void setMovements(int *newMovements);

    const vector<int> &getMovement() const;
    void setMovement(const vector<int> &newMovement);

    void saveMovement(int n);

    bool getColides() const;
    void setColides(bool newColides);

    int getCurrentMove() const;
    void setCurrentMove(int newCurrentMove);

private:
    QPixmap sprite;
    QTimer *timer;

public slots:
    void moveGhost();
};

#endif // GHOST_H
