#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QPixmap>
#include <QtGui>
#include <QPushButton>



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    // main window
    MainWindow w;

    w.show();

    return a.exec();
}
