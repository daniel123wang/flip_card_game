#include "grade.h"
#include "ui_grade.h"
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
grade::grade(QWidget *parent, int res, int glevel, int letterpasscount, int mistake) :
    QMainWindow(parent),
    ui(new Ui::grade)
{
       ui -> setupUi(this);
       this->setWindowTitle("Flip!");
       this->setFixedSize(800,610);
       QString FinalGrade;
       QString WrongMatch;

       QCursor cursor;
       QPixmap pixmap(":/image/pointer.png");
       QSize picSize(50, 50);
       QPixmap scaledPixmap = pixmap.scaled(picSize, Qt::KeepAspectRatio);
       cursor = QCursor(scaledPixmap, 2, 2);
       this->setCursor(cursor);

       if(letterpasscount == 0){
           if(res == 0){
               FinalGrade = "Final Grade: P";
               QFont f = QFont("Helvetica", 17);
               QString text("<font color='white'>%1</font><br>"
                               "<font color='white'>%2</font>");
           }else{
               FinalGrade = "Final Grade: NP";
               QFont f = QFont("Helvetica", 17);
               QString text("<font color='white'>%1</font><br>"
                               "<font color='white'>%2</font>");
           }
       }else{
           if(res == 0){
               if(mistake == 0){
                   FinalGrade = "Final Grade: A+";
               }else if(mistake == 1 | mistake == 2){
                   FinalGrade = "Final Grade: A";
               }else if(mistake>=3 && mistake <=5){
                   FinalGrade = "Final Grade: A-";
               }else if(mistake>5&&mistake<=8){
                   FinalGrade = "Final Grade: B";
               }else if(mistake>8 && mistake<=10){
                   FinalGrade = "Final Grade: C";
               }else{
                   FinalGrade = "Final Grade: D";
               }
               WrongMatch = "Number of Wrong Matches: ";
               WrongMatch.append(QString::number(mistake));
           }else{
               FinalGrade = "Final Grade: F";
           }

       }
       // Text of instructions
       QFont f = QFont("Chalkduster", 17);
       QString text("<font color='white'>%1</font><br>"
                       "<font color='white'>%2</font>");

       QLabel *label = new QLabel(this);
       label->setText(text.arg(FinalGrade,WrongMatch));
       label -> setFont(f);
       // Create "back" button
       QPushButton *back = new QPushButton("Back");
       back->setFixedSize(100,40);
       connect(back, SIGNAL(released()), this, SLOT(handleBack()));

       // Window layout
       QWidget *wid = new QWidget(this);
       QVBoxLayout *layout = new QVBoxLayout(this);
       layout->addWidget(label);
       layout->addWidget(back);

       QHBoxLayout *center = new QHBoxLayout(this);
       center->addSpacing(50);
       center->addLayout(layout);
       center->addSpacing(100);

       wid->setLayout(center);
       setCentralWidget(wid);

       // Window background
       QPixmap bkgnd(":/bkg_grade.jpg.jpg");
       bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
       QPalette palette;
       palette.setBrush(QPalette::Background, bkgnd);
       this->setPalette(palette);

}

/* This function is the constructor of a GameInstruction window that has a background.
 * @param evt is a QResizeEvent pointer.
 */
void grade::resizeEvent(QResizeEvent *evt)
{
    // Creating painter for background that can be resized according to window size
    QPixmap bkgnd(":/bkg_grade.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
    QMainWindow::resizeEvent(evt);

}

/* This function leads back to the main window
 */
void grade::handleBack()
{
    this->close();
    QWidget *parent = this->parentWidget();
    parent->show();
}

/* This function is the destructor of a MainWindow that has a background.
 */
grade::~grade()
{
    delete ui;
}

