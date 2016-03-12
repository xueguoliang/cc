#include "Stone.h"

Stone::Stone()
{

}

Stone::~Stone()
{

}

void Stone::init(int idx)
{
    Type types[] = {
        CHE, MA, XIANG, SHI, JIANG, SHI, XIANG, MA, CHE,
        PAO, PAO,
        BING, BING, BING, BING, BING,
        BING, BING, BING, BING, BING,
        PAO, PAO,
        CHE, MA, XIANG, SHI, JIANG, SHI, XIANG, MA, CHE
    };
    int rows[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        2, 2,
        3, 3, 3, 3, 3,
        6, 6, 6, 6, 6,
        7, 7,
        9, 9, 9, 9, 9, 9, 9, 9, 9
    };
    int cols[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8,
           1,                7,
        0,    2,    4,    6,    8,
        0,    2,    4,    6,    8,
           1,                7,
        0, 1, 2, 3, 4, 5, 6, 7, 8
    };

    this->_type = types[idx];
    this->_dead = false;
    this->_col = cols[idx];
    this->_row = rows[idx];
    this->_idx = idx;
}

void Stone::draw(QPainter &p, int d, bool selected)
{
    if(_dead)return;

    QPoint center = pos(d);

    p.setPen(QPen(Qt::black, 2));
    if(selected)
        p.setBrush(Qt::darkGray);
    else
        p.setBrush(Qt::yellow);
    p.drawEllipse(center, d/2, d/2);

    QString str;
    if(isRed())
    {
        str = "帅仕相车马炮兵";
        p.setPen(Qt::red);
    }
    else
    {
        str = "将士象车马炮卒";
        p.setPen(Qt::black);
    }


    p.setFont(QFont("Arial", d/1.5));

    p.drawText(rect(d), str.mid((int)_type, 1), QTextOption(Qt::AlignCenter));
}

QPoint Stone::pos(int d)
{
    return QPoint(_col*d, _row*d);
}

QRect Stone::rect(int d)
{
    QPoint center = pos(d);
    QRect rc(center-QPoint(d/2-5, d/2-5), center+QPoint(d/2-5, d/2-5));
    return rc;
}

