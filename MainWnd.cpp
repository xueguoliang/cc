#include "MainWnd.h"
#include <QHBoxLayout>
MainWnd::MainWnd(QWidget *parent) : QMainWindow(parent)
{
    QWidget* w = new QWidget;
    setCentralWidget(w);

    QHBoxLayout* lay = new QHBoxLayout(w);
    lay->addWidget(_board = new Board);
}

MainWnd::~MainWnd()
{

}

