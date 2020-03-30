#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "gameinstruction.h"
#include "gamelevel.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMediaPlayer>

/* @file mainwindow.h
 @brief This is the class definition for main windows.
 @author Jue Wang, Xinpei Li, Suyuan Liu
 @date 11/09/2018

 This file is the class declaration for the MainWindow class.
It includes a constructor that creates the MainWindow with a background and a resizeEvent that allow the background to be full screen size.
 */

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *evt);
    ~MainWindow();

private slots:
    void handleExit();
    void handleInstruction();
    void handleLevel();

private:
    Ui::MainWindow *ui;
    QPushButton *exit_button;
    QPushButton *instruction;
    QPushButton *level;
    QMediaPlayer *player;
    GameInstruction *ins = nullptr;
    GameLevel *lev = nullptr;

};

#endif // MAINWINDOW_H
