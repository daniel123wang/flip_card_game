#include "gamelevel.h"
#include "ui_gamelevel.h"
#include "gradechoice.h"
#include "mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QPixmap>
#include <QtGui>
#include <QPushButton>

/* @file gamelevel.cpp
 @brief This is the class definition for game levels.
 @author Jue Wang, Xinpei Li, Suyuan Liu
 @date 11/09/2018

 This file is the class definition for the GameLevel class.
It includes a constructor that creates the GameLevel and links to game pages.
 */

/* This function is the constructor of a GameLevel that has a background.
 */
GameLevel::GameLevel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameLevel)
{
       ui -> setupUi(this);
       this->setWindowTitle("Flip!");
       this->setFixedSize(800,610);

       QCursor cursor;
       QPixmap pixmap(":/image/pointer.png");
       QSize picSize(50, 50);
       QPixmap scaledPixmap = pixmap.scaled(picSize, Qt::KeepAspectRatio);
       cursor = QCursor(scaledPixmap, 2, 2);
       this->setCursor(cursor);

       easy = new QPushButton("Easy", this);
       easy->setFixedSize(130,20);
       connect(easy, SIGNAL (released()), this, SLOT (easy_pressed()));

       medium = new QPushButton("Medium", this);
       medium->setFixedSize(130,20);
       connect(medium, SIGNAL (released()), this, SLOT (medium_pressed()));

       hard = new QPushButton("Hard",this);
       hard->setFixedSize(130,20);
       connect(hard, SIGNAL (released()), this, SLOT (hard_pressed()));

       // Create "back" button
       QPushButton *back = new QPushButton("Back");
       back->setFixedSize(130,20);
       connect(back, SIGNAL(released()), this, SLOT(handleBack()));

       QHBoxLayout *layout = new QHBoxLayout(this);
       layout->addWidget(easy);
       layout->addWidget(medium);
       layout->addWidget(hard);
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

/* This function is the constructor of a GameLevel that has a background.
 * @param evt is a QResizeEvent pointer.
 */
void GameLevel::resizeEvent(QResizeEvent *evt)
{
    // Creating painter for background that can be resized according to window size
    QPixmap bkgnd(":/bkg_level.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
    QMainWindow::resizeEvent(evt);

}

/* This function links push button "easy" with the game page for "easy"
 */
void GameLevel::easy_pressed()
{
    if (new_gradechoice != nullptr)
            new_gradechoice->close();
    new_gradechoice = new GradeChoice(this, 3);
    new_gradechoice->show();
    this->hide();

    /*if (new_game != nullptr)
        new_game->close();
    new_game = new Game(this, 3);
    new_game->show();
    this->hide();
    */
}

/* This function links push button "medium" with the game page for "medium"
 */
void GameLevel::medium_pressed()
{
    if (new_gradechoice != nullptr)
            new_gradechoice->close();
    new_gradechoice = new GradeChoice(this, 5);
    new_gradechoice->show();
    this->hide();
}

/* This function links push button "hard" with the game page for "hard"
 */
void GameLevel::hard_pressed()
{

    if (new_gradechoice != nullptr)
            new_gradechoice->close();
    new_gradechoice = new GradeChoice(this, 6);
    new_gradechoice->show();
    this->hide();
}

/* This function leads back to the main window
 */
void GameLevel::handleBack()
{
    this->close();
    MainWindow * mw = new MainWindow(this);
    mw->show();
}

/* This function is the destructor of a GameLevel.
 */
GameLevel::~GameLevel()
{
    delete ui;
}
