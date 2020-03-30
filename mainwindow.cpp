#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QtGui>
#include <QMediaPlayer>


/* @file mainwindow.cpp
 @brief This is the class definition for main windows.
 @author Jue Wang, Xinpei Li, Suyuan Liu
 @date 11/09/2018

 This file is the class definition for the MainWindow class.
It includes a constructor that creates the MainWindow with a background and a resizeEvent that allow the background to be full screen size.
 */

/* This function is the constructor of a MainWindow that has a background.
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
      ui->setupUi(this);
      this->setWindowTitle("Flip!");
      this->setFixedSize(800,610);

      QCursor cursor;
      QPixmap pixmap(":/image/pointer.png");
      QSize picSize(50, 50);
      QPixmap scaledPixmap = pixmap.scaled(picSize, Qt::KeepAspectRatio);
      cursor = QCursor(scaledPixmap, 2, 2);
      this->setCursor(cursor);


      // Background Music
      QMediaPlayer *bgm = new QMediaPlayer;
      bgm->setMedia(QUrl("qrc:/Game-Menu.mp3"));
      bgm->setVolume(50);
      bgm->play();

      // Push button to exit
      exit_button = new QPushButton("Exit", this);
      exit_button->setFixedSize(130,20);
      connect(exit_button, SIGNAL (released()), this, SLOT (handleExit()));

      // Push button to game instruction
      instruction = new QPushButton("Instruction", this);
      instruction -> setFixedSize(130, 20);
      connect(instruction, SIGNAL (released()), this, SLOT (handleInstruction()));

      // Push button to game level
      level = new QPushButton("Levels", this);
      level -> setFixedSize(130, 20);
      connect(level, SIGNAL (released()), this, SLOT (handleLevel()));
      connect(level, SIGNAL (released()), bgm, SLOT (stop()));

//      QMovie *movie = new QMovie(":/image/mw.gif");
//      QLabel *processLabel = new QLabel(this);
//      processLabel->setMovie(movie);
//      movie->start();

      // Window layout
      QHBoxLayout *layout = new QHBoxLayout(this);
      QVBoxLayout *overall = new QVBoxLayout(this);
      layout ->addWidget(level);
      layout ->addWidget(instruction);
      layout ->addWidget(exit_button);
//      overall -> addWidget(label);
//      overall->addWidget(processLabel);
      for(int i=0; i<10;i++){
          overall->addStretch();
      }
      overall -> addLayout(layout);
      overall->addStretch();

      QWidget *overallwidget = new QWidget(this);
      overallwidget->setLayout(overall);
      setCentralWidget(overallwidget);

      // Creates background
       QPixmap bkgnd(":/bkg_main.jpg");
       bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
       QPalette palette;
       palette.setBrush(QPalette::Background, bkgnd);
       this->setPalette(palette);
}

/* This function is the constructor of a MainWindow that has a background.
 * @param evt is a QResizeEvent pointer.
 */
void MainWindow::resizeEvent(QResizeEvent *evt)
{
    // Creating painter for background that can be resized according to window size
    QPixmap bkgnd(":/bkg_main.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
    QMainWindow::resizeEvent(evt);

}

/* This function exits the main window
 */
void MainWindow::handleExit()
{
    this->close();
}

/* This function links to game instruction
 */
void MainWindow::handleInstruction()
{
    this->hide();
    if (ins != nullptr)
        ins->close();
    ins = new GameInstruction(this);
    ins -> show();

}

/* This function ledas to game level selection
 */
void MainWindow::handleLevel()
{
    this->hide();
    if(lev != nullptr)
        lev -> close();
    lev = new GameLevel(this);
    lev->show();
}

/* This function is the destructor of a MainWindow that has a background.
 */
MainWindow::~MainWindow()
{
    delete ui;
}
