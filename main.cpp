#include <QApplication>
#include "MainWnd.h"

int main(int argc, char**argv)
{
    QApplication app(argc, argv);

    MainWnd wnd;
    wnd.show();

    return app.exec();
}
