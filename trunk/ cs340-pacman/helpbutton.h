/*-------------------
Name:   Rafe "Ali" Choudhry
Course: CS 340
-------------------*/

#ifndef HELPBUTTON_H
#define HELPBUTTON_H


#include<QWidget>
#include <QPushButton>
#include <QLabel>
#include <QWidget>


class helpbutton : public QWidget
{//start header file
    Q_OBJECT
public:
    helpbutton(QWidget *parent =0);

public:
    QPushButton *help_Button;

};//end header file


#endif // HELPBUTTON_H
