#ifndef RESULT_H
#define RESULT_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class result;
}

/* @file GameInstruction.h
 @brief This is the class definition for the result class.
 @author Jue Wang, Xinpei Li, Suyuan Liu
 @date 11/09/2018

 This file is the class declaration for the GameInstruction class, which shows the game instruction in a separate window.
 */

class result : public QMainWindow
{
    Q_OBJECT

public:

    explicit result(QWidget *parent = nullptr, int n = 0, int lev = 0, int lp = 0, int wrong = 0);
    void resizeEvent(QResizeEvent *evt);
    ~result();

private slots:
    void handleAgain();
    void handleLevel();
    void handleExit();
    void handleGrade();

private:
    Ui::result *ui;
    int glevel;
    int letterpasscount;
    int res;
    int mistake;

};

#endif // RESULT_H
