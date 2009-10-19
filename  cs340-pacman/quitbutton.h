/*-------------------
Name:   Rafe "Ali" Choudhry
Course: CS 340
-------------------*/
#ifndef QUITBUTTON_H
#define QUITBUTTON_H

#include<QWidget>
#include <QPushButton>
#include <QLabel>
#include <QWidget>


class quitbutton : public QWidget
{//start header file
    Q_OBJECT
public:
    quitbutton(QWidget *parent =0);

public:
    QPushButton *quit_Button;

};//end header file





#endif // QUITBUTTON_H

