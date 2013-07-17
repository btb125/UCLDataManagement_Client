#include <QApplication>
#include <QDebug>

#include "ViewMainScreen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ViewMainScreen w;
    w.showMaximized() ;

    //...
    return a.exec();
}
