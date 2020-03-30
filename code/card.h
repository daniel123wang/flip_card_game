#ifndef CARD_H
#define CARD_H

#include <QPixmap>
#include <QWidget>
#include <QtGui>
#include <QMediaPlayer>


/* @file card.h
 @brief This is the class definition for the Card class.
 @author Jue Wang, Xinpei Li, Suyuan Liu
 @date 11/09/2018

 This file is the class declaration for the Card class, it stores all the cards and checks if they match.
 */

namespace Ui {
class card;
}


class card : public QWidget
{
    Q_OBJECT

public:
    void paintEvent(QPaintEvent *);
    void reveal();
    void hideback();
    void checkmark();
    void shake();


    explicit card(QWidget *parent = 0, QPixmap* card_name = nullptr);
    void mousePressEvent(QMouseEvent *event);

    bool equals(card* b);
    ~card();

private:
    QPixmap* pic = nullptr;
    QPixmap* back = new QPixmap(":/image/pokerback.jpg");
    QPixmap* tick = new QPixmap(":/image/check.jpg");
    bool backside = true;
    bool checked = false;

    Ui::card *ui;
    double x;
    double y;
friend class Game;
};


#endif // CARD_H
