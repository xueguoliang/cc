#include "AI.h"
#include "Board.h"

/* 32个棋子的得分表 */
static int score[7][10][9] =
{
    /* 将 */
    {
        {050, 050, 050, 30000, 30000, 30000, 050, 050, 050},
        {050, 050, 050, 30000, 30000, 30000, 050, 050, 050},
        {050, 050, 050, 30000, 30000, 30000, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 30000, 30000, 30000, 050, 050, 050},
        {050, 050, 050, 30000, 30000, 30000, 050, 050, 050},
        {050, 050, 050, 30000, 30000, 30000, 050, 050, 050},
    },

    /*士*/
    {
        {050, 050, 050, 010, 050, 010, 050, 050, 050},
        {050, 050, 050, 050, 010, 050, 050, 050, 050},
        {050, 050, 050, 010, 050, 010, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 010, 050, 010, 050, 050, 050},
        {050, 050, 050, 050, 010, 050, 050, 050, 050},
        {050, 050, 050, 010, 050, 010, 050, 050, 050},
    },

    /*象*/
    {
        {050, 050, 010, 050, 050, 050, 010, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {010, 050, 050, 050, 010, 050, 050, 050, 010},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 010, 050, 050, 050, 010, 050, 050},
        {050, 050, 010, 050, 050, 050, 010, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {010, 050, 050, 050, 010, 050, 050, 050, 010},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 010, 050, 050, 050, 010, 050, 050},
    },

    /*车*/
    {
        {100, 100, 100, 100, 100, 100, 100, 100, 100},
        {100, 100, 100, 100, 100, 100, 100, 100, 100},
        {100, 100, 100, 100, 100, 100, 100, 100, 100},
        {100, 100, 100, 100, 100, 100, 100, 100, 100},
        {100, 100, 100, 100, 100, 100, 100, 100, 100},
        {100, 100, 100, 100, 100, 100, 100, 100, 100},
        {100, 100, 100, 100, 100, 100, 100, 100, 100},
        {100, 100, 100, 100, 100, 100, 100, 100, 100},
        {100, 100, 100, 100, 100, 100, 100, 100, 100},
        {100, 100, 100, 100, 100, 100, 100, 100, 100},
    },

    /*马*/
    {
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
    },

    /*炮*/
    {
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
        {050, 050, 050, 050, 050, 050, 050, 050, 050},
    },

    /*兵*/
    {
        {020, 020, 020, 020, 020, 020, 020, 020, 020},
        {020, 020, 020, 020, 020, 020, 020, 020, 020},
        {020, 020, 020, 020, 020, 020, 020, 020, 020},
        {020, 020, 020, 020, 020, 020, 020, 020, 020},
        {020, 020, 020, 020, 020, 020, 020, 020, 020},
        {020, 020, 020, 020, 020, 020, 020, 020, 020},
        {020, 020, 020, 020, 020, 020, 020, 020, 020},
        {020, 020, 020, 020, 020, 020, 020, 020, 020},
        {020, 020, 020, 020, 020, 020, 020, 020, 020},
        {020, 020, 020, 020, 020, 020, 020, 020, 020},
    },
};


AI::AI(Board& board):_board(board)
{

}

AI::~AI()
{

}

Step AI::getStep(int level)
{
    Steps steps;
    getAllPossibleMove(steps);

    Step* best;
    int curMaxScore = -MAX_SCORE;

    for(auto it = steps.begin(); it!=steps.end(); ++it)
    {
        Step* step = *it;
        fakeMove(*step);

        /* 如果在这一层能够有一步直接吃掉对方老将，那就直接走这个吧 */
        if(BlackWin())
        {
            best = step;
            unfakeMove(*step);
            break;
        }

        int value = getMinScore(level-1, curMaxScore);
        unfakeMove(*step);

        if(value > curMaxScore)
        {
            curMaxScore = value;
            best = step;
        }
    }

    Step ret(*best);
    return ret;
}

int AI::getMaxScore(int level, int cut)
{
    if(level == 0)
    {
        return eval();
    }

    Steps steps;
    getAllPossibleMove(steps);

    int curMaxScore = -MAX_SCORE;

    for(auto it = steps.begin(); it!=steps.end(); ++it)
    {
        Step* step = *it;
        fakeMove(*step);
        if(BlackWin())
        {
            unfakeMove(*step);
            return MAX_SCORE-1;
        }
        int value = getMinScore(level-1, curMaxScore);
        unfakeMove(*step);

        if(value >= cut)
            return value;

        if(value >= curMaxScore)
        {
            curMaxScore = value;
        }
    }

    return curMaxScore;
}

int AI::getMinScore(int level, int cut)
{
    if(level == 0)
    {
        return eval();
    }

    Steps steps;
    getAllPossibleMove(steps);

    int curMinScore = MAX_SCORE;

    for(auto it = steps.begin(); it!=steps.end(); ++it)
    {
        Step* step = *it;
        fakeMove(*step);
        if(RedWin())
        {
            unfakeMove(*step);
            return -MAX_SCORE+1;
        }
        int value = getMaxScore(level-1, curMinScore);
        unfakeMove(*step);

        if(value <= cut)
            return value;

        if(value < curMinScore)
        {
            curMinScore = value;
        }
    }

    return curMinScore;
}

int AI::eval()
{
    int bScore = 0;
    int rScore = 0;
    for(int i=0; i<16; ++i)
    {
        Stone& s = _board._stone[i];
        if(s.isDead())continue;

        bScore += score[s.type()][s.row()][s.col()];
    }

    for(int i=16; i<32; ++i)
    {
        Stone& s = _board._stone[i];
        if(s.isDead())continue;

        rScore += score[s.type()][9-s.row()][8-s.col()];
    }

    return bScore - rScore;
}

void AI::testMove(Steps &steps, Stone &stone, QPoint pts[], int count)
{
    for(int i=0 ;i<count; ++i)
    {
        QPoint& pt = pts[i];
        if(isOutofRange(pt))
            continue;

        int aimId = _board.getStone(pt.x(), pt.y());
        if(aimId != -1 && _board.isRed(aimId) == stone.isRed())
            continue;

        if(_board.canMove(stone.idx(), pt.x(), pt.y(), aimId))
        {
            Step* step = new Step;
            step->_moveid = stone.idx();
            step->_killid = aimId;
            step->_rowFrom = stone.row();
            step->_colFrom = stone.col();
            step->_rowTo = pt.x();
            step->_colTo = pt.y();

            steps.append(step);
        }
    }
}

void AI::getAllPossibleMoveJiang(Steps &steps, Stone & stone)
{
    int row = stone.row();
    int col = stone.col();

    int row1, col1;
    if(stone.idx() == 4)
    {
        row1 = _board._stone[27].row();
        col1 = _board._stone[27].col();
    }
    else
    {
        row1 = _board._stone[4].row();
        col1 = _board._stone[4].col();
    }

    QPoint pts[] = {
        QPoint(row, col+1),
        QPoint(row, col-1),
        QPoint(row+1, col),
        QPoint(row-1, col),
        QPoint(row1, col1)
    };

    testMove(steps, stone, pts, sizeof(pts)/sizeof(*pts));
}

void AI::getAllPossibleMoveShi(Steps &steps, Stone &stone)
{
    int row = stone.row();
    int col = stone.col();
    QPoint pts[] = {
        QPoint(row+1, col+1),
        QPoint(row-1, col-1),
        QPoint(row+1, col-1),
        QPoint(row-1, col+1)
    };
    testMove(steps, stone, pts, sizeof(pts)/sizeof(*pts));
}

void AI::getAllPossibleMoveXiang(Steps &steps, Stone &stone)
{
    int row = stone.row();
    int col = stone.col();
    QPoint pts[] = {
        QPoint(row+2, col+2),
        QPoint(row-2, col-2),
        QPoint(row+2, col-2),
        QPoint(row-2, col+2)
    };
    testMove(steps, stone, pts, sizeof(pts)/sizeof(*pts));
}

void AI::getAllPossibleMoveChe(Steps &steps, Stone &stone)
{
    int row = stone.row();
    int col = stone.col();
    QPoint pts[] = {
        QPoint(row, 0),
        QPoint(row, 1),
        QPoint(row, 2),
        QPoint(row, 3),
        QPoint(row, 4),
        QPoint(row, 5),
        QPoint(row, 6),
        QPoint(row, 7),
        QPoint(row, 8),

        QPoint(0, col),
        QPoint(1, col),
        QPoint(2, col),
        QPoint(3, col),
        QPoint(4, col),
        QPoint(5, col),
        QPoint(6, col),
        QPoint(7, col),
        QPoint(8, col),
        QPoint(9, col),
    };
    testMove(steps, stone, pts, sizeof(pts)/sizeof(*pts));
}

void AI::getAllPossibleMoveMa(Steps &steps, Stone &stone)
{
    int row = stone.row();
    int col = stone.col();
    QPoint pts[] = {
        QPoint(row+2, col+1),
        QPoint(row-2, col-1),
        QPoint(row+2, col-1),
        QPoint(row-2, col+1),

        QPoint(row+1, col+2),
        QPoint(row-1, col-2),
        QPoint(row+1, col-2),
        QPoint(row-1, col+2)
    };
    testMove(steps, stone, pts, sizeof(pts)/sizeof(*pts));
}

void AI::getAllPossibleMovePao(Steps &steps, Stone &stone)
{
    getAllPossibleMoveChe(steps, stone);
}

void AI::getAllPossibleMoveBing(Steps &steps, Stone &stone)
{
    int row = stone.row();
    int col = stone.col();
    QPoint pts[] = {
        QPoint(row, col+1),
        QPoint(row, col-1),
        QPoint(row+1, col),
        QPoint(row-1, col),
    };
    testMove(steps, stone, pts, sizeof(pts)/sizeof(*pts));
}

void AI::getAllPossibleMove(Steps &steps)
{
    int m1=0, m2=16;
    if(_board._bRedTurn)
    {
        m1 = 16, m2=32;
    }

    for(int i=m1; i<m2; ++i)
    {
        Stone& s = _board._stone[i];
        if(s.isDead()) continue;

        switch (s.type())
        {
        case Stone::JIANG:
            getAllPossibleMoveJiang(steps, s);
            break;
        case Stone::SHI:
            getAllPossibleMoveShi(steps, s);
            break;
        case Stone::XIANG:
            getAllPossibleMoveXiang(steps, s);
            break;
        case Stone::CHE:
            getAllPossibleMoveChe(steps, s);
            break;
        case Stone::MA:
            getAllPossibleMoveMa(steps, s);
            break;
        case Stone::PAO:
            getAllPossibleMovePao(steps, s);
            break;
        case Stone::BING:
            getAllPossibleMoveBing(steps, s);
            break;
        default:
            break;
        }
    }
}

void AI::fakeMove(Step &step)
{
    _board.fakeMove(step._moveid, step._rowTo, step._colTo, step._killid);
}

void AI::unfakeMove(Step &step)
{
    _board.unfakeMove(step._moveid, step._rowFrom, step._colFrom, step._killid);
}

bool AI::BlackWin()
{
    return _board._stone[27].isDead();
}

bool AI::RedWin()
{
    return _board._stone[4].isDead();
}





