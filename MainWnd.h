#ifndef MAINWND_H
#define MAINWND_H

#include <QMainWindow>
#include "Board.h"

class MainWnd : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWnd(QWidget *parent = 0);
    ~MainWnd();

    Board* _board;
signals:

public slots:
};

#endif // MAINWND_H
