//Written by: Nikolas Pensyl
#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::cout<<"test";
    Widget w;
    w.show();
    return a.exec();
}
