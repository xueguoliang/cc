#ifndef AI_H
#define AI_H

#include <QList>
#include <QPoint>
class Board;
class Stone;

#define MAX_SCORE 0x3fffffff

class Step
{
public:
    int _moveid;
    int _killid;
    int _rowFrom;
    int _rowTo;
    int _colFrom;
    int _colTo;
    int _moveScore;
};

class Steps : public QList<Step*>
{
public:
    ~Steps()
    {
        while(!isEmpty())
        {
            delete *begin();
            removeFirst();
        }
    }
};

class AI
{
public:
    AI(Board& board);
    ~AI();

    Board& _board;

    int _curEval;

    Step getStep(int level);
    int getMaxScore(int level, int cut);
    int getMinScore(int level, int cut);

    int getStoneScore(int idx, int row, int col);
    int getMoveScore(int moveid, int row, int col, int killid);

    int eval();
    void getAllPossibleMoveJiang(Steps&, Stone&);
    void getAllPossibleMoveShi(Steps&, Stone&);
    void getAllPossibleMoveXiang(Steps&, Stone&);
    void getAllPossibleMoveChe(Steps&, Stone&);
    void getAllPossibleMoveMa(Steps&, Stone&);
    void getAllPossibleMovePao(Steps&, Stone&);
    void getAllPossibleMoveBing(Steps&, Stone&);
    void getAllPossibleMove(Steps&);
    void fakeMove(Step& step);
    void unfakeMove(Step& step);
    bool isOutofRange(QPoint pt)
    {
        int row = pt.x();
        int col = pt.y();
        if(row < 0 || row > 9) return true;
        if(col < 0 || col > 8) return true;
        return false;
    }
    void testMove(Steps&, Stone&, QPoint[], int);

    bool BlackWin();
    bool RedWin();

};

#endif // AI_H
