#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <QMainWindow>
#include "gradechoice.h"
#include <QPushButton>

/* @file gamelevel.h
 @brief This is the class definition for the window of game level.
 @author Jue Wang, Xinpei Li, Suyuan Liu
 @date 11/09/2018

 This file is the class declaration for the GameLevel class.
It includes a constructor that creates a window for selecting game level.
 */

namespace Ui {
class GameLevel;
}

class GameLevel : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameLevel(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *evt);
    ~GameLevel();
private slots:
    void easy_pressed();
    void medium_pressed();
    void hard_pressed();
    void handleBack();



private:
    Ui::GameLevel *ui;
    //Game* new_game = nullptr;
    GradeChoice* new_gradechoice = nullptr;

    QPushButton* easy;
    QPushButton* medium;
    QPushButton* hard;

};

#endif // GAMELEVEL_H
