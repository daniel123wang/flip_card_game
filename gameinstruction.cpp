#include "gameinstruction.h"
#include "ui_gameinstruction.h"
#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QPixmap>
#include <QtGui>
#include <QPushButton>

/* @file gameinstruction.cpp
 @brief This is the class definition for gameinstruction.
 @author Jue Wang, Xinpei Li, Suyuan Liu
 @date 11/09/2018

 This file is the class definition for the gameinstruction class.
It includes a constructor that creates a game instruction page, a function ensure background can be full-screen size and a destructor.
 */

/* This function is the constructor of a game instruction window.
@param parent is the base window
 */
GameInstruction::GameInstruction(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameInstruction)
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

       // Text of instructions
       QString instruction("Here are the instruction: ");
       QString instruction2("Try to memorize all pairs of cards in given time period. When time runs out, all cards will be flipped to the backside. Try to match all the pairs in the following timespan. The number of cards and time for memorization and matching depends on the level of difficulty you choose. Choosing to be letter graded will allow you to check the number of mistakes you made, while PNP only shows if you pass the level or not. Enjoy! ");
       QFont f = QFont("Chalkduster", 17);
       QString text("<font color='white'>%1</font><br>"
                       "<font color='white'>%2</font>");

       QLabel *label = new QLabel(this);
       label->setText(text.arg(instruction,instruction2));
       label -> setFont(f);
       label->setWordWrap(true);

       // Create "back" button
       QPushButton *back = new QPushButton("Back");
       back->setFixedSize(100,40);
       connect(back, SIGNAL(released()), this, SLOT(handleBack()));

       // Window layout
       QWidget *wid = new QWidget(this);
       QVBoxLayout *layout = new QVBoxLayout(this);
       layout->addStretch();
       layout->addWidget(label);
       QHBoxLayout *center = new QHBoxLayout(this);
       center->addStretch();
       center->addWidget(back);
       center->addStretch();

       layout->addLayout(center);
       layout->addStretch();
       wid->setLayout(layout);
       setCentralWidget(wid);

       // Window background
       QPixmap bkgnd(":/bkg.jpg");
       bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
       QPalette palette;
       palette.setBrush(QPalette::Background, bkgnd);
       this->setPalette(palette);

}

/* This function is the constructor of a GameInstruction window that has a background.
 * @param evt is a QResizeEvent pointer.
 */
void GameInstruction::resizeEvent(QResizeEvent *evt)
{
    // Creating painter for background that can be resized according to window size
    QPixmap bkgnd(":/bkg.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
    QMainWindow::resizeEvent(evt);

}

/* This function leads back to the main window
 */
void GameInstruction::handleBack()
{
    this->close();
    QWidget *parent = this->parentWidget();
    parent->show();
}

/* This function is the destructor of a MainWindow that has a background.
 */
GameInstruction::~GameInstruction()
{
    delete ui;
}

