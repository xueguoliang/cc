#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "Stone.h"

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);
    ~Board();

    void startGame();
    void initChess();

    Stone _stone[32];
    bool _bRedTurn;
    int _selectId;

    QPoint _ori;
    int _d;

    void paintEvent(QPaintEvent *);
    void drawJiugong(QPainter& p);
    void drawFlower(QPainter& p);
    void drawRiver(QPainter& p);
    void resizeEvent(QResizeEvent *);

    QPoint c1(int row, int col);

signals:

public slots:
};

#endif // BOARD_H
