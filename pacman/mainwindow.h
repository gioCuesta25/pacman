#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>
#include <QTimer>
#include <QElapsedTimer>
#include "laberinto.h"
#include "pacman.h"
#include "ghost.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QPixmap laberintoPixmap;
    QPixmap laberintoPixmaps[32];
    QPixmap lifePacmanPixmap;
    QGraphicsPixmapItem* m_labyrinthPixmapItems[28][36];
    Laberinto laberinto;
    Pacman* pac;
    Ghost* inky;
    Ghost* blinky;
    Ghost* pinky;
    Ghost* clyde;
    QGraphicsSimpleTextItem* score_text_item;
    QTimer* timer;
    int score_value = 0, prize_size = 0;
    QElapsedTimer m_elapsedTimer;
    bool isOver;
    float m_deltaTime, m_loopTime;
    const float m_loopSpeed;

    void loadPixmap();
    void initLaberinto(QGraphicsScene* scene);
    void renderLaberinto();
    void keyPressEvent(QKeyEvent *event);
    bool checkColision();
    bool checkGhostsColision(QGraphicsItem* ghost);
    void initGUI(QGraphicsScene* scene);
    void defineGhostMove(Ghost* ghost);
    bool colidesWithGhost();

public slots:
    void updatePacmanSprite();
    void moveGhosts();
    void loop();
    void teleport();
    void checkWin();
};
#endif // MAINWINDOW_H
