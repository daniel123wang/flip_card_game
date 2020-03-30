#include "result.h"
#include "ui_result.h"
#include "gamelevel.h"
#include "grade.h"
#include <QApplication>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QPixmap>
#include <QtGui>
#include <QPushButton>

/* @file result.cpp
 @brief This is the class definition for results.
 @author Jue Wang, Xinpei Li, Suyuan Liu
 @date 11/09/2018

 This file is the class definition for the result class.
It includes a constructor that creates a result page, a function ensure background can be full-screen size and a destructor.
 */

/* This function is the constructor of a result window.
@param parent is the base window
 */
result::result(QWidget *parent, int n, int lev,int lp, int wrong) :
    QMainWindow(parent),
    ui(new Ui::result)
{
       ui -> setupUi(this);
       this->setWindowTitle("Flip!");
       this->setFixedSize(800,610);
       glevel = lev;
       letterpasscount= lp;
       res = n;
       mistake = wrong;

       QCursor cursor;
       QPixmap pixmap(":/image/pointer.png");
       QSize picSize(50, 50);
       QPixmap scaledPixmap = pixmap.scaled(picSize, Qt::KeepAspectRatio);
       cursor = QCursor(scaledPixmap, 2, 2);
       this->setCursor(cursor);

       QLabel *processLabel = new QLabel(this);
       // when win and letter grade
       if (n ==0 && lp == 1){

           QMediaPlayer *win = new QMediaPlayer;
           win->setMedia(QUrl("qrc:/Win.mp3"));
           win->setVolume(50);
           win->play();

           QMediaPlayer *youwin = new QMediaPlayer;
           youwin->setMedia(QUrl("qrc:/YouWin.mp3"));
           youwin->play();

           QMovie *movie = new QMovie(":/image/flower.gif");

           processLabel->setMovie(movie);
           movie->start();

       }
       //lose and letter grade
       else if (n ==1 && lp ==1){

           QMediaPlayer *lose = new QMediaPlayer;
           lose->setMedia(QUrl("qrc:/Lose.mp3"));
           lose->setVolume(50);
           lose->play();

           QMediaPlayer *youlose = new QMediaPlayer;
           youlose->setMedia(QUrl("qrc:/YouLose.mp3"));
           youlose->play();
       }
       //win and pnp
       else if (n ==0 && lp == 0){
           QMediaPlayer *win = new QMediaPlayer;
           win->setMedia(QUrl("qrc:/Win.mp3"));
           win->setVolume(50);
           win->play();

           QMediaPlayer *youwin = new QMediaPlayer;
           youwin->setMedia(QUrl("qrc:/YouWin.mp3"));
           youwin->play();

           QMovie *movie = new QMovie(":/image/flower.gif");

           processLabel->setMovie(movie);
           movie->start();

       }
       //lose and pnp
       else if (n==1 && lp== 0){
           QMediaPlayer *lose = new QMediaPlayer;
           lose->setMedia(QUrl("qrc:/Lose.mp3"));
           lose->setVolume(50);
           lose->play();

           QMediaPlayer *youlose = new QMediaPlayer;
           youlose->setMedia(QUrl("qrc:/YouLose.mp3"));
           youlose->play();
       }


       // Create "try again" button
       QPushButton *again = new QPushButton("Try again?");
       again->setFixedSize(100,40);
       connect(again, SIGNAL(released()), this, SLOT(handleAgain()));

       // Create "Game Level" button
       QPushButton *level = new QPushButton("Different Level");
       level->setFixedSize(150,40);
       connect(level, SIGNAL(released()), this, SLOT(handleLevel()));

       // Create "Exit" button
       QPushButton *exit = new QPushButton("Exit");
       exit->setFixedSize(100,40);
       connect(exit, SIGNAL(released()), this, SLOT(handleExit()));

       // Create grade pushbutton
       QPushButton *grade = new QPushButton("See Grade");
       grade->setFixedSize(120,40);
       connect(grade, SIGNAL(released()), this, SLOT(handleGrade()));

       // Create layout for pushbuttons
       QHBoxLayout *pushbuttons = new QHBoxLayout(this);
       pushbuttons->addWidget(grade);
       pushbuttons->addWidget(again);
       pushbuttons->addWidget(level);
       pushbuttons->addWidget(exit); 

       // Window layout
       QWidget *wid = new QWidget(this);
       QVBoxLayout *layout = new QVBoxLayout(this);
       for(int i=0; i<10; i++){
           layout->addStretch();
       }
       layout->addWidget(processLabel);
       layout->addLayout(pushbuttons);
       layout->addStretch();
       wid->setLayout(layout);
       setCentralWidget(wid);

        //Window background
       QPixmap bkgnd(":/bkg.jpg");
       bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
       QPalette palette;
       palette.setBrush(QPalette::Background, bkgnd);
       this->setPalette(palette);

}

/* This function is the constructor of a GameInstruction window that has a background.
 * @param evt is a QResizeEvent pointer.
 */
void result::resizeEvent(QResizeEvent *evt)
{
    // Creating painter for background that can be resized according to window size
    if(res == 0){
        QPixmap bkgnd(":/youwin.jpg");
        bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
        QPalette p = palette();
        p.setBrush(QPalette::Background, bkgnd);
        setPalette(p);
        QMainWindow::resizeEvent(evt);
    }else{
        QPixmap bkgnd(":/youlose.jpg");
        bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
        QPalette p = palette();
        p.setBrush(QPalette::Background, bkgnd);
        setPalette(p);
        QMainWindow::resizeEvent(evt);
    }
}

/* This function leads back to the main window
 */
void result::handleAgain()
{
    this->close();
    Game *newgame = new Game(this, glevel, letterpasscount);
    newgame->show();

}

/* This function exits the main window
 */
void result::handleExit()
{
    this->close();
}

/* This function links to game instruction
 */
void result::handleLevel()
{
    this->hide();
    GameLevel *newgamelevel = new GameLevel(this);
    newgamelevel->show();

}

/*this is to show the new grade*/
void result::handleGrade(){
    this->hide();
    grade *newgrade = new grade(this, res, glevel, letterpasscount, mistake);
    newgrade->show();
}

/* This function is the destructor of a MainWindow that has a background.
 */
result::~result()
{
    delete ui;
}
