#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "Stone.h"
#include "AI.h"

// cmpjsxbCMPJSXB

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
    int _ids[10][9];

    AI _ai;

    QPoint _ori;
    int _d;

    int getStone(int row, int col)
    {
        return _ids[row][col];
    }

    void paintEvent(QPaintEvent *);
    void drawJiugong(QPainter& p);
    void drawFlower(QPainter& p);
    void drawRiver(QPainter& p);

    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *);
    void trySelectStone(QPoint pt);
    void tryMoveStone(QPoint pt);

    int d1(int moveid, int row, int col)
    {
        int drow = qAbs(row-r(moveid));
        int dcol = qAbs(col-c(moveid));
        return drow*10+dcol;
    }
    bool canMoveJiang(int moveid, int row, int col, int killid);
    bool canMoveShi(int moveid, int row, int col, int killid);
    bool canMoveXiang(int moveid, int row, int col, int killid);
    bool canMoveChe(int moveid, int row, int col, int killid);
    bool canMoveMa(int moveid, int row, int col, int killid);
    bool canMovePao(int moveid, int row, int col, int killid);
    bool canMoveBing(int moveid, int row, int col, int killid);

    bool canMove(int moveid, int row, int col, int killid);
    bool isRed(int id){return _stone[id].isRed();}
    int getStoneCount(int row1, int col1, int row2, int col2);

    void moveStone(int moveid, int row, int col, int killid);
    void checkGameOver();

    void fakeMove(int moveid, int row, int col, int killid, int moveScore);
    void unfakeMove(int moveid, int row, int col, int killid, int moveScore);

    QPoint c1(int row, int col);
    bool t1(QPoint pt, int&row, int& col);
    int r(int id){return _stone[id].row();}
    int c(int id){return _stone[id].col();}
    void setRowCol(int id, int row, int col)
    {
        _stone[id].setRow(row);
        _stone[id].setCol(col);
    }
signals:

public slots:
};

#endif // BOARD_H
