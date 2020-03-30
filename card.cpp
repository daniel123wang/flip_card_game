#include "card.h"
#include <iostream>
#include "ui_card.h"
#include <QPainter>

/* @file card.cpp
 @brief This is the class definition for cards.
 @author Jue Wang, Xinpei Li, Suyuan Liu
 @date 11/09/2018

 This file is the class definition for the card class.
It includes a constructor that creates a card and a function that checks if two cards match.
 */

/* This function is the constructor of a card object.
@param card_name is a pointer to a picture that contains the pattern of a card.
 */
card::card(QWidget *parent, QPixmap* card_name) :
    QWidget(parent),pic(card_name),
    ui(new Ui::card)
{
    ui -> setupUi(this);

    x = 0.0;
    y = 0.0;
}

/*this function is to shake the card when you click two different cards
*/
void card::shake(){
    QPropertyAnimation *pAnimation = new QPropertyAnimation(this, "pos");
        pAnimation->setDuration(300);
        pAnimation->setLoopCount(2);
        pAnimation->setKeyValueAt(0, QPoint(geometry().x() - 3, geometry().y() - 3));
        pAnimation->setKeyValueAt(0.1, QPoint(geometry().x() + 6, geometry().y() + 6));
        pAnimation->setKeyValueAt(0.2, QPoint(geometry().x() - 6, geometry().y() + 6));
        pAnimation->setKeyValueAt(0.3, QPoint(geometry().x() + 6, geometry().y() - 6));
        pAnimation->setKeyValueAt(0.4, QPoint(geometry().x() - 6, geometry().y() - 6));
        pAnimation->setKeyValueAt(0.5, QPoint(geometry().x() + 6, geometry().y() + 6));
        pAnimation->setKeyValueAt(0.6, QPoint(geometry().x() - 6, geometry().y() + 6));
        pAnimation->setKeyValueAt(0.7, QPoint(geometry().x() + 6, geometry().y() - 6));
        pAnimation->setKeyValueAt(0.8, QPoint(geometry().x() - 6, geometry().y() - 6));
        pAnimation->setKeyValueAt(0.9, QPoint(geometry().x() + 3, geometry().y() + 3));
        pAnimation->setKeyValueAt(1, QPoint(geometry().x(), geometry().y()));
        pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        repaint();
        QCoreApplication::processEvents();
}

/*This function is to print the back and front side of the card
*/
void card::paintEvent(QPaintEvent *){
    QPainter painter(this);
    if(backside == true){
        painter.drawPixmap(x, y, 110, 130, *back);
    }
    else{
        painter.drawPixmap(x, y, 110, 130, *pic);
    }

}


void card::checkmark(){
    checked = true;
//    repaint();
//    QCoreApplication::processEvents();
    return;
}

/*this funciton is to print the front side of the card*/
void card::reveal(){
    backside = false;
    repaint();
    QCoreApplication::processEvents();
    return;
}

/*this function is to print the back side of the card*/
void card::hideback(){
    backside = true;
    repaint();
    QCoreApplication::processEvents();
    return;
}

/*
this function is to set the sound when click cards
*/
void card::mousePressEvent(QMouseEvent *event){
    QMediaPlayer *flip = new QMediaPlayer;
    flip->setMedia(QUrl("qrc:/CardFlip.mp3"));
    flip->play();

    backside = false;
    repaint();
    QCoreApplication::processEvents();



    return;
}

/* This function checks if two cards are equal.
@param b is the card being compared to.
 */
bool card::equals(card* b){
    return (pic == b->pic);
}

card::~card(){
    delete ui;
}
