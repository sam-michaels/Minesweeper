#include "mainwindow.h"

#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // qDebug() << "Current working directory:" << QDir::currentPath();
    w.show();
    return a.exec();
}
