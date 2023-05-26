#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QBrush>
#include <QColor>
#include <QPixmap>
#include <iostream>
#include <QSize>
#include <QRectF>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "pacman.h"
#include "ghost.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
     m_loopSpeed(int(1000/16))
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setMinimumSize(QSize(530, 630));
    setMaximumSize(QSize(530, 630));

//    ui->graphicsView->setMinimumSize(QSize(450, 600));
//    ui->graphicsView->setMaximumSize(QSize(450, 600));

    ui->graphicsView->setFixedSize(455,600);

    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Ocultar la barra de desplazamiento vertical
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    loadPixmap();

    pac= new Pacman(":/images/things.png");
    inky = new Ghost(":/images/things.png", 3, 200, 220,3, 1);
    blinky = new Ghost(":/images/things.png", 1, 220, 410,6, 2);
    pinky = new Ghost(":/images/things.png", 2, 240, 110,5, 3);
    clyde = new Ghost(":/images/things.png", 4, 290, 320,3, 4);

    QGraphicsScene *scene = new QGraphicsScene();
    scene->setBackgroundBrush(QBrush(QColor(0,0,0)));

    ui->graphicsView->setScene(scene);

    // Elementos del juego (Pacman y fantasmas)
    scene->addItem(pac);
    scene->addItem(inky);
    scene->addItem(blinky);
    scene->addItem(pinky);
    scene->addItem(clyde);


    initLaberinto(scene);
    initGUI(scene);

    timer = new QTimer(this);
    timer->setInterval(100);

    // Slots y signals
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePacmanSprite()));
    connect(timer, SIGNAL(timeout()), this, SLOT(moveGhosts()));
    connect(timer, SIGNAL(timeout()), this, SLOT(loop()));
    connect(timer, SIGNAL(timeout()), this, SLOT(teleport()));
    timer->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadPixmap()
{
    laberintoPixmap.load(":/images/labyrinth.png");
}

void MainWindow::initLaberinto(QGraphicsScene *scene)
{
    int index = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            laberintoPixmaps[index] = laberintoPixmap.copy(i * 16, j * 16, 16, 16);
            index++;
        }
    }

    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 36; j++) {
            m_labyrinthPixmapItems[i][j] =  new QGraphicsPixmapItem();
            m_labyrinthPixmapItems[i][j]->setPixmap(laberintoPixmaps[ laberinto.getPieces(i, j) ]);
            m_labyrinthPixmapItems[i][j]->setPos(i*16, j*16);
            scene->addItem(m_labyrinthPixmapItems[i][j]);
        }
    }
}

void MainWindow::renderLaberinto()
{
    for (int i = 0; i < int(28); i++)
    {
        for (int j = 0; j < int(36); j++)
        {
            m_labyrinthPixmapItems[i][j]->setPixmap(laberintoPixmaps[ laberinto.getPieces(i, j) ]);
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //Funcion que reconoce la tecla que fue oprimida
    if(event->key()==Qt::Key_D && !isOver){
        pac->setSprite_position(3);
        pac->MoveRight();
        if(checkColision()){
            pac->MoveLeft();
        }
    }
    // x = 431, 270
    else if(event->key()==Qt::Key_W && !isOver){
        pac->setSprite_position(0);
        pac->MoveUp();
        if(checkColision()){
            pac->MoveDown();
        }
    }

    else if(event->key()==Qt::Key_S && !isOver){
        pac->setSprite_position(1);
        pac->MoveDown();
        if(checkColision()){
            pac->MoveUp();
        }
    }

    else if(event->key()==Qt::Key_A && !isOver){
        pac->setSprite_position(2);
        pac->MoveLeft();
        if(checkColision()){
            pac->MoveRight();
        }
    }

    if (colidesWithGhost()) {
        score_text_item->setPos(10*16, 8);
        score_text_item->setText("Final Score: " + QString::number(score_value).right(5));
        timer->stop();
    }
}

bool MainWindow::checkColision()
{
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 36; j++) {
            if (m_labyrinthPixmapItems[i][j]->collidesWithItem(pac) && laberinto.getPieces(i, j) != 26) {
                return true;
            } else if (m_labyrinthPixmapItems[i][j]->collidesWithItem(pac) && laberinto.getPieces(i, j) == 26) {
                m_labyrinthPixmapItems[i][j]->setPixmap(QPixmap());
                score_value++;
                score_text_item->setText("Score: " + QString::number(score_value).right(5));

                return false;
            }
        }
    }

    return false;
}

bool MainWindow::checkGhostsColision(QGraphicsItem *ghost)
{
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 36; j++) {
            if (m_labyrinthPixmapItems[i][j]->collidesWithItem(ghost) && laberinto.getPieces(i, j) != 26) {
                return true;
            }
        }
    }

    return false;
}

void MainWindow::initGUI(QGraphicsScene *scene)
{
    /*
     * Esta funcion se encarga de pintar en la escena algunos
     * elementos de la interfaz gráficos como el puntaje
    */

    score_text_item = new QGraphicsSimpleTextItem();
    score_text_item->setFont(QFont("Arial", 14));
    score_text_item->setBrush(QBrush(QColor(255,255,255)));
    score_text_item->setPen(QPen(QColor(255, 255, 255)));
    score_text_item->setPos(12*16, 8);
    score_text_item->setText("Score: " + QString::number(score_value).right(5));

    scene->addItem(score_text_item);
}

void MainWindow::defineGhostMove(Ghost *ghost)
{
    bool colides = checkGhostsColision(ghost);

    srand(time(NULL));
    int number = (rand() % 4) + 1;

    if (colides) {
        if (ghost->getCurrentMove() == 1) {
            ghost->MoveLeft();
        } else if (ghost->getCurrentMove() == 2) {
            ghost->MoveDown();
        } else if (ghost->getCurrentMove() == 3) {
            ghost->MoveRight();
        } else if (ghost->getCurrentMove() == 4) {
            ghost->MoveUp();
        }

        do {
            number = (rand() % 4) + 1;
        } while (ghost->getCurrentMove() == number);

        ghost->setCurrentMove(number);
    }

    if (ghost->getCurrentMove() == 1) {
        ghost->MoveRight();
    } else if (ghost->getCurrentMove() == 2) {
        ghost->MoveUp();
    } else if (ghost->getCurrentMove() == 3) {
        ghost->MoveLeft();
    } else if (ghost->getCurrentMove() == 4) {
        ghost->MoveDown();
    }
}

bool MainWindow::colidesWithGhost()
{
    if (pac->collidesWithItem(inky) || pac->collidesWithItem(blinky) || pac->collidesWithItem(pinky) || pac->collidesWithItem(clyde)) {
        isOver = true;
        return true;
    }

    return false;
}

void MainWindow::updatePacmanSprite()
{
    if (pac->getSprite_end() != 60) {
        pac->setSprite_end(pac->getSprite_end() + 30);
    } else {
        pac->setSprite_end(0);
    }

    this->ui->graphicsView->scene()->update();
}

void MainWindow::moveGhosts()
{
    defineGhostMove(inky);
    defineGhostMove(pinky);
    defineGhostMove(blinky);
    defineGhostMove(clyde);
}

void MainWindow::loop()
{

}

void MainWindow::teleport()
{
    QPointF objectPos = pac->scenePos();
    QRectF viewRect = this->ui->graphicsView->viewport()->rect();

    if (!viewRect.contains(objectPos)) {
        cout << "Te estas saliendo del mapa" << endl;
    }
}

void MainWindow::checkWin()
{
    if (!isOver && score_value == 244) {
        isOver = true;
        score_text_item->setPos(10*16, 8);
        score_text_item->setText("You Win: " + QString::number(score_value).right(5));
        timer->stop();
    }
}

// Numero total de moneditas: 244
