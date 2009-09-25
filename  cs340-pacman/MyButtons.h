#ifndef MYBUTTONS_H
#define MYBUTTONS_H
#include<QWidget>
class QPushButton;
class QLabel;
class QWidget;

class MyButtons : public QWidget
{
    Q_OBJECT
public:
    MyButtons(QWidget *parent =0);
    //MyButtons(QGraphicsScene *parent =0);
private slots:
    void displayInstructions();
    //void quit();
private:
    QPushButton *help_Button;
    QPushButton *quit_Button;
    QPushButton *play_Button;

};
#endif // MYBUTTONS_H
