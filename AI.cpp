#include "AI.h"
#include "Board.h"

/* 棋子的得分表 */
static int score[7][10][9] =
{
    /* 将 */
    {
        {30000, 30000, 30001, 30005, 30001, 30000, 30000, 30000, 30000},
        {30000, 30000, 29992, 29992, 29992, 30000, 30000, 30000, 30000},
        {30000, 30000, 29991, 29991, 29991, 30000, 30000, 30000, 30000},
        {30000, 30000, 30000, 30000, 30000, 30000, 30000, 30000, 30000},
        {30000, 30000, 30000, 30000, 30000, 30000, 30000, 30000, 30000},

        {30000, 30000, 30000, 30000, 30000, 30000, 30000, 30000, 30000},
        {30000, 30000, 30000, 30000, 30000, 30000, 30000, 30000, 30000},
        {30000, 30000, 29991, 29991, 29991, 30000, 30000, 30000, 30000},
        {30000, 30000, 29992, 29992, 29992, 30000, 30000, 30000, 30000},
        {30000, 30000, 30001, 30005, 30001, 30000, 30000, 30000, 30000},
    },

    /*士*/
    {
        {200, 200, 200, 200, 200, 200, 200, 200, 200},
        {200, 200, 200, 200, 206, 200, 200, 200, 200},
        {200, 200, 200, 200, 200, 200, 200, 200, 200},
        {200, 200, 200, 200, 200, 200, 200, 200, 200},
        {200, 200, 200, 200, 200, 200, 200, 200, 200},

        {200, 200, 200, 200, 200, 200, 200, 200, 200},
        {200, 200, 200, 200, 200, 200, 200, 200, 200},
        {200, 200, 200, 200, 200, 200, 200, 200, 200},
        {200, 200, 200, 200, 206, 200, 200, 200, 200},
        {200, 200, 200, 200, 200, 200, 200, 200, 200},
    },

    /*象*/
    {
        {200, 200, 200, 200, 200, 200, 200, 200, 200},
        {200, 200, 200, 200, 200, 200, 200, 200, 200},
        {196, 200, 200, 200, 206, 200, 200, 200, 196},
        {200, 200, 200, 200, 200, 200, 200, 200, 200},
        {200, 200, 200, 200, 200, 200, 200, 200, 200},

        {200, 200, 200, 200, 200, 200, 200, 200, 200},
        {200, 200, 200, 200, 200, 200, 200, 200, 200},
        {196, 200, 200, 200, 206, 200, 200, 200, 196},
        {200, 200, 200, 200, 200, 200, 200, 200, 200},
        {200, 200, 200, 200, 200, 200, 200, 200, 200},
    },

    /*车*/
    {
        {988 , 1012, 1008, 1024, 1000, 1024, 1008, 1012, 988 },
        {1010, 1016, 1012, 1024, 1000, 1024, 1012, 1016, 1010},
        {996 , 1016, 1012, 1024, 1000, 1024, 1012, 1016, 996 },
        {1008, 1018, 1008, 1024, 1024, 1024, 1008, 1018, 1008},
        {1016, 1024, 1024, 1028, 1030, 1028, 1024, 1024, 1016},

        {1016, 1022, 1022, 1028, 1030, 1028, 1022, 1022, 1016},
        {1012, 1026, 1026, 1032, 1032, 1032, 1026, 1026, 1012},
        {1012, 1016, 1014, 1028, 1032, 1028, 1014, 1016, 1012},
        {1012, 1024, 1018, 1032, 1066, 1032, 1018, 1024, 1012},
        {1012, 1016, 1014, 1026, 1028, 1026, 1014, 1016, 1012},
    },

    /*马*/
    {
        {450, 444, 454, 450, 454, 450, 454, 444, 450},
        {444, 454, 458, 460, 430, 460, 458, 454, 444},
        {460, 458, 462, 464, 458, 464, 462, 458, 460},
        {458, 462, 470, 464, 470, 464, 470, 462, 458},
        {454, 470, 476, 478, 480, 478, 476, 470, 454},

        {454, 474, 472, 480, 482, 480, 472, 474, 454},
        {460, 490, 474, 488, 474, 488, 474, 490, 460},
        {458, 470, 472, 480, 472, 480, 472, 470, 458},
        {454, 466, 480, 468, 462, 468, 480, 466, 454},
        {454, 454, 454, 466, 454, 466, 454, 454, 454},
    },

    /*炮*/
    {
        {500, 500, 502, 506, 506, 506, 502, 500, 500},
        {500, 502, 504, 504, 504, 504, 504, 502, 500},
        {502, 500, 508, 506, 510, 506, 508, 500, 502},
        {500, 500, 500, 500, 500, 500, 500, 500, 500},
        {499, 500, 506, 500, 508, 500, 506, 500, 499},

        {500, 500, 500, 500, 508, 500, 500, 500, 500},
        {500, 506, 506, 504, 508, 504, 506, 506, 500},
        {502, 502, 500, 490, 492, 490, 500, 502, 502},
        {504, 504, 500, 492, 486, 492, 500, 504, 504},
        {508, 508, 500, 490, 488, 490, 500, 508, 508},
    },

    /*兵*/
    {
        {100, 100, 100, 100, 100, 100, 100, 100, 100},
        {100, 100, 100, 100, 100, 100, 100, 100, 100},
        {100, 100, 100, 100, 100, 100, 100, 100, 100},
        {98 , 100, 98 , 100, 112, 100, 98 , 100, 98 },
        {106, 100, 108, 100, 114, 100, 108, 100, 106},

        {120, 136, 144, 170, 180, 170, 144, 136, 120},
        {140, 154, 160, 180, 182, 180, 160, 154, 140},
        {140, 160, 190, 210, 210, 210, 190, 160, 140},
        {140, 160, 200, 230, 270, 230, 200, 160, 140},
        {100, 100, 100, 104, 108, 104, 100, 100, 100},
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

int AI::getStoneScore(int idx, int row, int col)
{
    if(idx == -1)
        return 0;

    if(idx < 16)
        return score[_board._stone[idx].type()][row][col];

    return score[_board._stone[idx].type()][9-row][8-col];
}

int AI::getMoveScore(int moveid, int row, int col, int killid)
{
    int ret = getStoneScore(killid, row, col);

    ret += getStoneScore(moveid, row, col) -
            getStoneScore(moveid, _board.r(moveid), _board.c(moveid));

    return ret;
}


int AI::eval()
{
#if 0
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
#endif
    return _curEval;
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

            step->_moveScore = getMoveScore
                    (step->_moveid, step->_rowTo, step->_colTo, step->_killid);

            /* 应该找地方插入 */
            auto it=steps.begin();
            for(; it!=steps.end(); ++it)
            {
                Step* pos = *it;
                if(step->_moveScore > pos->_moveScore)
                    break;
            }
            steps.insert(it, step);
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
    _board.fakeMove(step._moveid, step._rowTo, step._colTo, step._killid, step._moveScore);
}

void AI::unfakeMove(Step &step)
{
    _board.unfakeMove(step._moveid, step._rowFrom, step._colFrom, step._killid, step._moveScore);
}

bool AI::BlackWin()
{
    return _board._stone[27].isDead();
}

bool AI::RedWin()
{
    return _board._stone[4].isDead();
}





