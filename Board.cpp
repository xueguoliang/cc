#include "Board.h"

Board::Board(QWidget *parent) : QWidget(parent)
{
    startGame();
}

Board::~Board()
{

}

void Board::startGame()
{
    initChess();
    _bRedTurn = true;
    _selectId = -1;
}

void Board::initChess()
{
    for(int i=0; i<32; ++i)
    {
        this->_stone[i].init(i);
    }
}

void Board::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.translate(_ori);

    /* 绘制棋盘 */
    for(int i=0; i<10; ++i)
    {
        if(i==0 || i==9)
        {
            p.setPen(QPen(Qt::black, 2));
        }
        else
        {
            p.setPen(QPen(Qt::black, 1));
        }

        p.drawLine(QPoint(0, i*_d), QPoint(8*_d, i*_d));
    }

    for(int i=0; i<9; ++i)
    {
        if(i==0||i==8)
        {
            p.setPen(QPen(Qt::black, 2));
            p.drawLine(QPoint(i*_d, 0), QPoint(i*_d, 9*_d));
        }
        else
        {
            p.setPen(QPen(Qt::black, 1));
            p.drawLine(QPoint(i*_d, 0), QPoint(i*_d, 4*_d));
            p.drawLine(QPoint(i*_d, 5*_d), QPoint(i*_d, 9*_d));
        }
    }

    drawJiugong(p);
    drawFlower(p);
    drawRiver(p);

    for(int i=0; i<32; ++i)
    {
        _stone[i].draw(p, _d, i==_selectId);
    }
}

void Board::drawJiugong(QPainter &p)
{
    p.setPen(QPen(Qt::black, 1));
    p.drawLine(c1(0, 3), c1(2, 5));
    p.drawLine(c1(2, 3), c1(0, 5));
    p.drawLine(c1(7, 3), c1(9, 5));
    p.drawLine(c1(9, 3), c1(7, 5));
}

void Board::drawFlower(QPainter &p)
{
    QPoint pts[] = {
        {2, 1}, {2, 7}, {3, 0}, {3, 2}, {3, 4}, {3, 6}, {3, 8},
        {7, 1}, {7, 7}, {6, 0}, {6, 2}, {6, 4}, {6, 6}, {6, 8},
    };

    p.setPen(QPen(Qt::black, 1));
    QPoint pos, start, end;
    int a=5, b=10;
    for(int i=0; i<(int)(sizeof(pts)/sizeof(*pts)); ++i)
    {
        pos = c1(pts[i].x(), pts[i].y());

        if(pts[i].y() != 0)
        {
            // 左
            start = pos + QPoint(-_d/b, -_d/b);
            end = start + QPoint(-_d/a, 0);
            p.drawLine(start, end);

            end = start + QPoint(0, -_d/a);
            p.drawLine(start, end);

            start = pos + QPoint(-_d/b, +_d/b);
            end = start + QPoint(-_d/a, 0);
            p.drawLine(start, end);

            end = start + QPoint(0, _d/a);
            p.drawLine(start, end);
        }

        if(pts[i].y() != 8)
        {
            // 右
            start = pos + QPoint(_d/b, _d/b);
            end = start + QPoint(_d/a, 0);
            p.drawLine(start, end);

            end = start + QPoint(0, _d/a);
            p.drawLine(start, end);

            start = pos + QPoint(_d/b, -_d/b);
            end = start + QPoint(_d/a, 0);

            p.drawLine(start, end);

            end = start + QPoint(0, -_d/a);
            p.drawLine(start, end);
        }
    }
}

void Board::drawRiver(QPainter &p)
{
    p.setPen(Qt::lightGray);
    p.setFont(QFont("宋体", _d/2, 700, false));
    {
        QPoint p1 = c1(4, 1);
        QPoint p2 = c1(5, 3);
        QRect rc(p1, p2);
        p.drawText(rc, "楚 河", QTextOption(Qt::AlignCenter));
    }
    {
        QPoint p1 = c1(4, 5);
        QPoint p2 = c1(5, 7);
        QRect rc(p1, p2);
        p.drawText(rc, "汉 界", QTextOption(Qt::AlignCenter));
    }
    p.setPen(Qt::black);
}

void Board::resizeEvent(QResizeEvent *)
{
    /* need init */
    QSize s = size();
    int d1 = s.width()/9;
    int d2 = s.height()/10;
    if(d1<d2)
    {
        _d = d1;
    }
    else
    {
        _d = d2;
    }

    QSize sBoard(_d*8, _d*9);
    QSize off = (s-sBoard)/2;
    _ori = QPoint(off.width(), off.height());
}

QPoint Board::c1(int row, int col)
{
    return QPoint(col*_d, row*_d);
}

