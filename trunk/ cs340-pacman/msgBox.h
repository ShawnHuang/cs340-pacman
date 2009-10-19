#ifndef MSGBOX_H
#define MSGBOX_H


//#include<QWidget>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
//#include <QWidget>


class msgBox
{//start header file
    //Q_OBJECT
public:
    //playbutton(QWidget *parent =0);
    msgBox();
public:
    QMessageBox *displayBox;
//public slots:
  //  void displayMap();
};//end header file


#endif // MSGBOX_H
