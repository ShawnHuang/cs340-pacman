/*-------------------
Name:   Rafe "Ali" Choudhry
Course: CS 340
-------------------*/

#ifndef TEST_H
#define TEST_H


#include<QWidget>
#include <QPushButton>
#include <QLabel>
#include "playbutton.h"
#include "msgBox.h"
#include <QMessageBox>
#include <QWidget>


class test : public QObject
{//start header file
    Q_OBJECT
public:
    //test(QWidget *parent =0);
test();
public:
    //QPushButton *play_Button;
    //playbutton *object;
    //msgBox *object1;
public slots:
    void displayMap();
};//end header file

#endif // TEST_H


