#include "gradechoice.h"
#include "ui_gradechoice.h"
#include "game.h"
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QPixmap>
#include <QtGui>
#include <QPushButton>

/* @file gradechoice.cpp
 @brief This is the class definition for GradeChoice.
 @author Jue Wang, Xinpei Li, Suyuan Liu
 @date 11/09/2018

 This file is the class definition for the GradeChoice class.
It includes a constructor that creates a Grade Choice page, a function to show letter grade and pnp.
 */

/*
This is the constructor of GradeChoice class*/
GradeChoice::GradeChoice(QWidget *parent, int glev) :
    QMainWindow(parent),
    ui(new Ui::GradeChoice)
{
       ui -> setupUi(this);
       levelcount = glev;
       this->setWindowTitle("Flip!");
       this->setFixedSize(800,610);

       QCursor cursor;
       QPixmap pixmap(":/image/pointer.png");
       QSize picSize(50, 50);
       QPixmap scaledPixmap = pixmap.scaled(picSize, Qt::KeepAspectRatio);
       cursor = QCursor(scaledPixmap, 2, 2);
       this->setCursor(cursor);

       letter = new QPushButton("LetterGrade", this);
       letter->setFixedSize(130,20);
       connect(letter, SIGNAL (released()), this, SLOT (lettergrade()));

       passnpass = new QPushButton("PNP", this);
       passnpass->setFixedSize(130,20);
       connect(passnpass, SIGNAL (released()), this, SLOT (pnp()));

       back = new QPushButton("Back", this);
       back->setFixedSize(130,20);
       connect(back, SIGNAL(released()), this, SLOT(handleBack()));

       QHBoxLayout *layout = new QHBoxLayout(this);
       layout->addWidget(letter);
       layout->addWidget(passnpass);
       layout->addWidget(back);

       QVBoxLayout *overall = new QVBoxLayout(this);
       overall->addStretch();
       overall->addStretch();
       overall ->addLayout(layout);
       overall->addStretch();
       overall->addStretch();

       QWidget *widget = new QWidget;
       widget->setLayout(overall);
       setCentralWidget(widget);

}
//letter grade lp = 1
void GradeChoice:: lettergrade(){
    if (new_game != nullptr)
        new_game->close();
    if (levelcount == 3){
        new_game = new Game(this, levelcount, 1);
        new_game->show();
        this->hide();
    }
    else if (levelcount == 5){
        new_game = new Game(this, levelcount, 1);
        new_game->show();
        this->hide();
    }
    else{
        new_game = new Game(this, levelcount, 1);
        new_game->show();
        this->hide();
    }
}

//pnp lp = 0
void GradeChoice::pnp(){

    if (new_game != nullptr)
        new_game->close();
    if (levelcount == 3){
        new_game = new Game(this, levelcount, 0);
        new_game->show();
        this->hide();
    }
    else if (levelcount == 5){
        new_game = new Game(this, levelcount, 0);
        new_game->show();
        this->hide();
    }
    else{
        new_game = new Game(this, levelcount, 0);
        new_game->show();
        this->hide();
    }
}

/*This is to back to the parent page
*/
void GradeChoice::handleBack(){
    this->close();
    QWidget *parent = this->parentWidget();
    parent->show();
}

/*
This is to set the background*/
void GradeChoice::resizeEvent(QResizeEvent *evt)
{
    // Creating painter for background that can be resized according to window size
    QPixmap bkgnd(":/bkg_grading.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
    QMainWindow::resizeEvent(evt);

}

GradeChoice::~GradeChoice()
{
    delete ui;
}

