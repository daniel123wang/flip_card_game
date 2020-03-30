#ifndef GAMEINSTRUCTION_H
#define GAMEINSTRUCTION_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class GameInstruction;
}

/* @file GameInstruction.h
 @brief This is the class definition for the GameInstruction class.
 @author Jue Wang, Xinpei Li, Suyuan Liu
 @date 11/09/2018

 This file is the class declaration for the GameInstruction class, which shows the game instruction in a separate window.
 */

class GameInstruction : public QMainWindow
{
    Q_OBJECT

public:

    explicit GameInstruction(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *evt);
    ~GameInstruction();

private slots:
    void handleBack();

private:
    Ui::GameInstruction *ui;

};

#endif // GAMEINSTRUCTION_H
