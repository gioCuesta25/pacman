#ifndef LABERINTO_H
#define LABERINTO_H

#include <QObject>

class Laberinto: public QObject
{
public:
    Laberinto();

    int getPieces(int x, int y) const;
    bool pieceBlocks(int x, int y);

    // Pendiente por realizar
//    bool removeDot();
private:
    int pieces[28][36];
    int NONE_FIELD = 30;
    int SMALL_DOT_FIELD = 26;
    int BIG_DOT_FIELD = 27;
};

#endif // LABERINTO_H
