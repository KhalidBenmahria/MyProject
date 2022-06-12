#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;




    //resize MainWindow
    w.resize(1000, 700);


    w.show();
    return a.exec();
}
