#ifndef STONE_H
#define STONE_H

#include <QPainter>

class Stone
{
public:
    Stone();
    ~Stone();

    enum Type {JIANG, SHI, XIANG, CHE, MA, PAO, BING};
    void init(int idx);
    void draw(QPainter& p, int d, bool selected);

    bool isDead(){return _dead;}
    void setDead(bool dead){_dead=dead;}

    void setRow(int row){_row=row;}
    void setCol(int col){_col=col;}
    int row(){return _row;}
    int col(){return _col;}

    bool isRed(){return _idx>=16;}
    void setIdx(quint8 idx){_idx=idx;}
    int idx(){return _idx;}

    void setType(Type t){_type=t;}
    Type type(){return _type;}

    QPoint pos(int d);
    QRect rect(int d);

private:
    Type _type;
    int _idx;
    bool _dead;
    int _row;
    int _col;
};

#endif // STONE_H
