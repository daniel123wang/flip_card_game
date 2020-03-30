#include "game.h"
#include "ui_game.h"
#include <QtGui>
#include <stdio.h>
#include <algorithm>
#include <cstdlib>
#include<random>
#include <ctime>
#include <unistd.h>
#include "gamelevel.h"
#include "mainwindow.h"

/* @file game.cpp
 @brief This is the class definition for game.
 @author Jue Wang, Xinpei Li, Suyuan Liu
 @date 11/09/2018

 This file is the class definition for the game class.
It includes a constructor that creates a game page, a function to exit the game and a destructor.
 */

/* This function is random generator function.
 */
int myrandom (int i) { return std::rand()%i;}

/* This function is the constructor of a game window.
@param parent is the base window
@param n is the game level being selected
 */
Game::Game(QWidget *parent, int n, int lp) :
    QMainWindow(parent),
    ui(new Ui::Game)
{
       ui -> setupUi(this);
       this->setWindowTitle("Flip!");
       this->setFixedSize(800,610);
       std::srand(std::time(NULL));
       num = n;
       num_two = 2*n;
       levelgame = n;
       letterpass = lp;

       QCursor cursor;
       QPixmap pixmap(":/image/pointer.png");
       QSize picSize(50, 50);
       QPixmap scaledPixmap = pixmap.scaled(picSize, Qt::KeepAspectRatio);
       cursor = QCursor(scaledPixmap, 2, 2);
       this->setCursor(cursor);

       // Randomize and duplicate the cards
       std::random_shuffle(six_cards.begin(), six_cards.end(),myrandom);
       for (int i = 0; i < n; i++){
           cards_in_game.push_back(six_cards[i]);
           cards_in_game.push_back(six_cards[i]);
       }
       std::random_shuffle(cards_in_game.begin(), cards_in_game.end(),myrandom);

       for(int i = 0; i < 2*n; ++i){
           cards_specific_level.push_back(new card(0, cards_in_game[i]));
       }

       for(int i = 0; i < 2*n; ++i){
           cards_specific_level[i]->installEventFilter(this);
       }

       // Set different layouts for different game levels
       for (int i = 0; i < 2*n; ++i){
           // Easy
           if(n==3){
               if(i<n){
                   row_one->addWidget(cards_specific_level[i]);
               }

               else{
                   row_two->addWidget(cards_specific_level[i]);
               }

           //Medium
           }else if(n == 5){
               if(i<n){
                   row_one->addWidget(cards_specific_level[i]);
               }
               else{
                   row_two->addWidget(cards_specific_level[i]);
               }
           //Hard
           }else if(n == 6){
               if(i<4){
                   row_one->addWidget(cards_specific_level[i]);
               }else if(i>=4 && i<8){
                   row_two->addWidget(cards_specific_level[i]);
               }else if(i>=8){
                   row_three->addWidget(cards_specific_level[i]);
               }
           }
       }

       // Set layout for different game level
       QVBoxLayout *cards = new QVBoxLayout;
       cards -> addLayout(row_one);
       cards -> addLayout(row_two);

       // Add a third row of cards if game level is hard
       if(n==6){
           cards->addLayout(row_three);
       }

       // Creates a Progressbar that changes with timer
       progressBar = new QProgressBar(this);
       progressBar->setRange(0, 100);
       progressBar->setValue(100);
       progressBar->setSizeIncrement(20,50);

       if(levelgame == 3){
           timeLine = new QTimeLine(4000, this);
       }else if(levelgame == 5){
           timeLine = new QTimeLine(8000, this);
       }else{
           timeLine = new QTimeLine(10000, this);
       }
       timeLine->setFrameRange(100, 0);
       connect(timeLine, SIGNAL(frameChanged(int)), progressBar, SLOT(setValue(int)));

       // Adds card shuffle sound
       QMediaPlayer *shuffle = new QMediaPlayer;
       shuffle->setMedia(QUrl("qrc:/CardShuffle.mp3"));

       // Clicking the push button will start the progress bar animation
       QPushButton *start = new QPushButton("Start", this);
       connect(start, SIGNAL(clicked()), this, SLOT(startnewgame()));
       connect(start, SIGNAL(clicked()), timeLine, SLOT(start()));
       connect(start, SIGNAL(clicked()), shuffle, SLOT(play()));
       start->setFixedSize(100,40);

       // Align push buttons "start", "back" and "quit".
       QHBoxLayout* push_button_line = new QHBoxLayout;

       QPushButton* quit = new QPushButton("Quit");
       quit->setFixedSize(100,40);
       connect(quit, SIGNAL (released()), this, SLOT (handleExit()));

       QPushButton* back = new QPushButton("Back");
       back->setFixedSize(100,40);
       connect(back, SIGNAL (released()), this, SLOT (handleBack()));

       push_button_line->addStretch();
       push_button_line->addWidget(start);
       push_button_line->addStretch();
       push_button_line->addWidget(back);
       push_button_line->addStretch();
       push_button_line->addWidget(quit);
       push_button_line->addStretch();

       // Final game page layout
       QVBoxLayout* overall = new QVBoxLayout;
       overall -> addWidget(progressBar);
       overall -> addLayout(cards);
       overall -> addLayout(push_button_line);

       QHBoxLayout* center = new QHBoxLayout;
       if(levelgame == 3){
           center->addSpacing(200);
           center->addLayout(overall);
           center->addSpacing(200);
       }else if(levelgame == 5){
           center->addSpacing(100);
           center->addLayout(overall);
           center->addSpacing(100);
       }else{
           center->addSpacing(100);
           center->addLayout(overall);
           center->addSpacing(100);
       }
       centralWidget()->setLayout(center);

       // Game page background
       QPixmap bkgnd(":/bkg.jpg");
       bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
       QPalette palette;
       palette.setBrush(QPalette::Background, bkgnd);
       this->setPalette(palette);
}

/*This function checks keeps track of all cards in the game. And there is a counter to track whether all cards are selected correctly
*/
bool Game::eventFilter(QObject *target, QEvent *event){

    for(int i = 0; i < 2*num; ++i){
        if(target == cards_specific_level[i]){
            if (event->type() == QEvent::MouseButtonPress){
                if(inspection == true){
                    return true;
                }
                else if(cards_specific_level[i]->checked == true){
                    return true;
                }
                else{
                if(two_cards.size() == 0)
                {
                two_cards.push_back(cards_specific_level[i]);
                index.push_back(i);
                return false;
                }
                else if(two_cards.size()==1){

                    QMediaPlayer *flip = new QMediaPlayer;
                    flip->setMedia(QUrl("qrc:/CardFlip.mp3"));
                    flip->play();

                    two_cards.push_back(cards_specific_level[i]);
                    index.push_back(i);
                    cards_specific_level[i]->reveal();
                    if(two_cards[0]->equals(two_cards[1]) && index[0]!=index[1]){
                        num_two -= 2;
                        if(num_two == 0){
                            timeLine_two->stop();
                            two_cards.clear();
                            index.clear();
                            showresult();
                            return true;
                        }
                        cards_specific_level[index[0]]->checkmark();
                        cards_specific_level[index[1]]->checkmark();
                        two_cards.clear();
                        index.clear();
                        return true;
                    }
                    else{
                        QMediaPlayer *wrongmatch = new QMediaPlayer;
                        wrongmatch->setMedia(QUrl("qrc:/WrongMatch.mp3"));
                        wrongmatch->play();
                        two_cards[0]->shake();
                        two_cards[1]->shake();

                        usleep(100000);
                        wrong++;
                        two_cards[0]->hideback();
                        two_cards[1]->hideback();
                        two_cards.clear();
                        index.clear();
                        return true;
                    }
                }
            }
        }
        }
    }
}

/* This function exits the game.
 */
void Game::handleExit()
{
    this->close();
    MainWindow * mw = new MainWindow(this);
    mw->show();
}


/* This function ledas to game level selection
 */
void Game::handleBack()
{
    if(timeLine!=nullptr){
    timeLine->stop();
    }
    if(timeLine_two!=nullptr){
    timeLine_two->stop();
    }
    this->hide();
    GameLevel *newgamelevel = new GameLevel(this);
    newgamelevel->show();
}

/*
This function start the playing after showing and letting players memorizing the cards*/
void Game::ontimeout(){
    inspection = false;
    for(int i = 0; i < 2*num; ++i){
        cards_specific_level[i]->hideback();
    }

    // Reset Progressbar for matching cards
    progressBar->reset();
    progressBar->setValue(100);
    progressBar->setSizeIncrement(20,50);

    if(levelgame == 3){
        timeLine_two =new QTimeLine(10000,this);
        timeLine_two ->setFrameRange(100, 0);
        connect(timeLine_two, SIGNAL(frameChanged(int)), progressBar, SLOT(setValue(int)));
        timeLine_two->start();
    }else if(levelgame == 5){
        timeLine_two =new QTimeLine(15000,this);
        timeLine_two ->setFrameRange(100, 0);
        connect(timeLine_two, SIGNAL(frameChanged(int)), progressBar, SLOT(setValue(int)));
        timeLine_two->start();
    }else{
        timeLine_two =new QTimeLine(20000,this);
        timeLine_two ->setFrameRange(100, 0);
        connect(timeLine_two, SIGNAL(frameChanged(int)), progressBar, SLOT(setValue(int)));
        timeLine_two->start();
    }


    connect(timeLine_two, SIGNAL(finished()), this, SLOT(showresult()));
}

/*this function shows the game result
*/
void Game::showresult(){
    if(num_two == 0){
        this->hide();
        if (res != nullptr)
            res->close();
        if (letterpass ==1){
            if (levelgame==3)
                res = new result(this, 0,3,letterpass,wrong);
            else if(levelgame ==5)
                res = new result(this, 0, 5,letterpass,wrong);
            else
                res = new result(this, 0, 6,letterpass,wrong);
        }
        if (letterpass ==0){
            if (levelgame==3)
                res = new result(this, 0,3,letterpass,wrong);
            else if(levelgame ==5)
                res = new result(this, 0, 5,letterpass,wrong);
            else
                res = new result(this, 0, 6,letterpass,wrong);
        }

        res -> show();
    }else{

        this->hide();
        if (res != nullptr)
            res->close();
        if (letterpass ==1){
            if (levelgame==3)
                res = new result(this, 1,3,letterpass);
            else if(levelgame ==5)
                res = new result(this, 1, 5,letterpass);
            else
                res = new result(this, 1, 6,letterpass);
        }
        if (letterpass ==0){
            if (levelgame==3)
                res = new result(this, 1,3,letterpass);
            else if(levelgame ==5)
                res = new result(this, 1, 5,letterpass);
            else
                res = new result(this, 1, 6,letterpass);

        }
        res -> show();
    }

}

/*this function starts the game
*/
void Game::startnewgame(){
    for(int i = 0; i < 2*num; ++i){
        cards_specific_level[i]->reveal();
    }
    inspection = true;
    connect(timeLine, SIGNAL(finished()), this, SLOT(ontimeout()));

}



/* This function is the destructor of the game class.
 */
Game::~Game()
{
    delete ui;
}



