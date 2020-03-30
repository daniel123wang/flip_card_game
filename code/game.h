#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <vector>
#include <QIcon>
#include <QLabel>
#include <algorithm>
#include <random>
#include <iostream>
#include <QProgressBar>
#include <QTimer>
#include <QMediaPlayer>
#include "card.h"
#include "result.h"

namespace Ui {
class Game;
}

/* @file game.h
 @brief This is the class definition for the Game class.
 @author Jue Wang, Xinpei Li, Suyuan Liu
 @date 11/09/2018

 This file is the class declaration for the Game class, which leads users to the game level accordingly.
 */

class Game : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr, int n = 0, int lp =0);
    Ui::Game *ui;

    ~Game();

private slots:
    void handleExit();
    void handleBack();
    void startnewgame();
    void ontimeout();
    void showresult();

private:
    bool win;
    int wrong = 0;
    double num;
    double num_two;
    int levelgame;
    int letterpass;
    std::vector<double> index;
    // Sotrage of all cards
    QPixmap* heitao_10 = new QPixmap(":/image/heitao_10.jpg");
    QPixmap* heitao_8 = new QPixmap(":/image/heitao_8.jpg");
    QPixmap* heitao_j = new QPixmap(":/image/heitao_j.jpg");
    QPixmap* heitao_k = new QPixmap(":/image/heitao_k.jpg");
    QPixmap* heitao_q = new QPixmap(":/image/heitao_q.jpg");
    QPixmap* hongxin_4 = new QPixmap(":/image/hongxin_4.jpg");
    QHBoxLayout* row_one = new QHBoxLayout;
    QHBoxLayout* row_two = new QHBoxLayout;
    QHBoxLayout* row_three = new QHBoxLayout;
    std::vector<QPixmap*> cards_in_game;
    std::vector<QPixmap*> six_cards = {heitao_10, heitao_8, heitao_j, heitao_k, heitao_q
                                      ,hongxin_4};
    std::vector<card*> cards_specific_level;
    std::vector<card*> two_cards;
    QTimeLine *timeLine = nullptr;
    QTimeLine *timeLine_two = nullptr;
    QProgressBar* progressBar = nullptr;
    result *res = nullptr;
    bool inspection = true;
    bool eventFilter(QObject *target, QEvent *event);

};

#endif // GAME_H
