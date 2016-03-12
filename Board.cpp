#include "Board.h"
#include <QMouseEvent>
#include <QDebug>
#include <QTimer>
#include <QApplication>

Board::Board(QWidget *parent) : QWidget(parent), _ai(*this)
{
    startGame();
}

Board::~Board()
{

}

void Board::startGame()
{
    for(int i=0; i<10; ++i)
    for(int j=0; j<9; ++j)
        _ids[i][j] = -1;

    initChess();
    _bRedTurn = true;
    _selectId = -1;
}

void Board::initChess()
{
    for(int i=0; i<32; ++i)
    {
        this->_stone[i].init(i);
        _ids[_stone[i].row()][_stone[i].col()] = i;
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

void Board::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton)
    {
        if(this->_selectId==-1)
        {
            trySelectStone(ev->pos());
        }
        else
        {
            tryMoveStone(ev->pos());
        }
    }
}

void Board::trySelectStone(QPoint pt)
{
    int row, col;
    bool b = t1(pt, row, col);
    if(!b) return;

    int stone = getStone(row, col);
    if(stone == -1)
        return;

    if(isRed(stone) != _bRedTurn)
        return;

    this->_selectId = stone;
    update();
}

void Board::tryMoveStone(QPoint pt)
{
    int row, col;
    bool b = t1(pt, row, col);
    if(!b) return;

    int stone = getStone(row, col);
    if(stone != -1)
    {
        if(_stone[stone].isRed()==_stone[_selectId].isRed())
        {
            _selectId = stone;
            update();
            return;
        }
    }

    if(canMove(_selectId, row, col, stone))
    {
        moveStone(_selectId, row, col, stone);
    }
}

bool Board::canMoveJiang(int moveid, int row, int col, int killid)
{
    if(killid != -1 && _stone[killid].type() == Stone::JIANG)
    {
        return canMoveChe(moveid, row, col, killid);
    }

    if(col<3||col>5)return false;
    if(row >2 && row<7) return false;

    int d = d1(moveid, row, col);
    if(d != 10 && d!=1) return false;

    return true;
}

bool Board::canMoveShi(int moveid, int row, int col, int )
{
    if(col<3||col>5)return false;
    if(row >2 && row<7) return false;

    int d = d1(moveid, row, col);
    if(d != 11) return false;

    return true;
}

bool Board::canMoveXiang(int moveid, int row, int col, int )
{
    if(isRed(moveid))
    {
        if(row < 5) return false;
    }
    else
    {
        if(row > 4) return false;
    }

    int d = d1(moveid, row, col);
    if(d != 22) return false;

    int mRow = (row+r(moveid))/2;
    int mCol = (col+c(moveid))/2;
    if(getStone(mRow, mCol) != -1) return false;

    return true;
}

bool Board::canMoveChe(int moveid, int row, int col, int )
{
    int ret = getStoneCount(r(moveid), c(moveid), row, col);
    return ret==0;
}

bool Board::canMoveMa(int moveid, int row, int col, int )
{
    int d = d1(moveid, row, col);
    if(d!=21 && d!=12)
        return false;

    if(d==21)
    {
        int mCol = c(moveid);
        int mRow = (r(moveid) + row)/2;
        if(getStone(mRow, mCol) != -1) return false;
    }
    else
    {
        int mCol = (c(moveid) + col)/2;
        int mRow = r(moveid);
        if(getStone(mRow, mCol) != -1) return false;
    }
    return true;
}

bool Board::canMovePao(int moveid, int row, int col, int killid)
{
    int ret = getStoneCount(r(moveid), c(moveid), row, col);
    if(killid != -1)
        return ret==1;


    return ret==0;
}

bool Board::canMoveBing(int moveid, int row, int col, int )
{
    int d = d1(moveid, row, col);
    if(d!=10 && d!=1)
        return false;

    if(isRed(moveid))
    {
        if(row > r(moveid))
            return false;
        if(r(moveid) >= 5 && row == r(moveid))
            return false;
    }
    else
    {
        if(row < r(moveid))
            return false;
        if(r(moveid) <= 4 && row == r(moveid))
            return false;
    }

    return true;
}

bool Board::canMove(int moveid, int row, int col, int killid)
{
    Stone::Type type = _stone[moveid].type();
    switch(type)
    {
    case Stone::JIANG:
        return canMoveJiang(moveid, row, col, killid);
    case Stone::SHI:
        return canMoveShi(moveid, row, col, killid);
    case Stone::XIANG:
        return canMoveXiang(moveid, row, col, killid);
    case Stone::CHE:
        return canMoveChe(moveid, row, col, killid);
    case Stone::MA:
        return canMoveMa(moveid, row, col, killid);
    case Stone::PAO:
        return canMovePao(moveid, row, col, killid);
    case Stone::BING:
        return canMoveBing(moveid, row, col, killid);
    }
    return false;
}

int Board::getStoneCount(int row1, int col1, int row2, int col2)
{
    int ret = 0;
    if(row1 != row2 && col1 != col2) return -1;
    if(row1==row2)
    {
        int m1 = col1 < col2 ? col1 : col2;
        for(int i=m1+1; i<col1+col2-m1; ++i)
        {
            if(getStone(row1, i) != -1) ++ret;
        }
    }
    else
    {
        int m1 = row1 < row2?row1 : row2;
        for(int i=m1+1; i<row1+row2-m1; ++i)
        {
            if(getStone(i, col1) != -1) ++ ret;
        }
    }

    return ret;
}

void Board::moveStone(int moveid, int row, int col, int killid)
{
    fakeMove(moveid, row, col, killid);
    update();

    if(this->_bRedTurn == false)
    {
        QTimer::singleShot(50, [&](){
            Step step = _ai.getStep(6);
            moveStone(step._moveid, step._rowTo, step._colTo, step._killid);
        });
    }
}

void Board::fakeMove(int moveid, int row, int col, int killid)
{
    if(killid != -1)
        _stone[killid].setDead(true);

    _ids[r(moveid)][c(moveid)] = -1;
    _ids[row][col] = moveid;

    setRowCol(moveid, row, col);
    _selectId = -1;
    _bRedTurn = !_bRedTurn;
}

void Board::unfakeMove(int moveid, int row, int col, int killid)
{
    if(killid != -1)
    {
        _stone[killid].setDead(false);
    }

    _ids[r(moveid)][c(moveid)] = killid;
    _ids[row][col] = moveid;

    setRowCol(moveid, row, col);
    _selectId = -1;
    _bRedTurn = !_bRedTurn;
}

QPoint Board::c1(int row, int col)
{
    return QPoint(col*_d, row*_d);
}

bool Board::t1(QPoint pt, int &row, int &col)
{
    int d = _d;
    pt = pt-_ori+QPoint(d/2, d/2);
    int idxs[] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10};
    int rowIdx = pt.y() / (d/2);
    int colIdx = pt.x() / (d/2);
    if(rowIdx < 0 || rowIdx > 19) return false;
    if(colIdx < 0 || colIdx > 17) return false;

    row = idxs[rowIdx];
    col = idxs[colIdx];

    return true;
}

