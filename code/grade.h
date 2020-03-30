#ifndef GRADE_H
#define GRADE_H


#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class grade;
}

/* @file GameInstruction.h
 @brief This is the class definition for the GameInstruction class.
 @author Jue Wang, Xinpei Li, Suyuan Liu
 @date 11/09/2018

 This file is the class declaration for the GameInstruction class, which shows the game instruction in a separate window.
 */

class grade : public QMainWindow
{
    Q_OBJECT

public:

    explicit grade(QWidget *parent = nullptr, int n=0, int glevel =0, int lp=0, int wrong=0 );
    void resizeEvent(QResizeEvent *evt);
    ~grade();

private slots:
    void handleBack();

private:
    Ui::grade *ui;

};

#endif // GRADE_H

