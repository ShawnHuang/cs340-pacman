/*-------------------
Name:   Rafe "Ali" Choudhry
Course: CS 340
-------------------*/


#include <QWidget>
#include "Menu.h"
#include <QFont>
#include <QMessageBox>
#include <QTimer>

Menu :: Menu(QGraphicsScene *scene) : QGraphicsView(scene)

{//start method

counter = 0;
    //timer = new QTimer;
    //QObject::connect(timer, SIGNAL(timeout()), this, SLOT(showHelp()));

    // Set the timer to trigger ever 1/3 of a second.
    //timer->start(1000 / 33);
    //create a toplevel object
    //TopLevel object1(&toplevelScene);
    //toplevelObject = new TopLevel(&toplevelScene);


    //set the view window
    this->resize(640,480);
    //this->setBackgroundBrush(QPixmap(".\back.jpg"));

    //add sprites

    //object = new sprites();
    //object1 = new ghost();


    //create helpbutton
    helpButton = new QPushButton (tr("Help"), this);
    helpButton->setFont(QFont("Lucida Handwriting",18,QFont::Bold));
    QObject:: connect(helpButton,SIGNAL(clicked()),this,SLOT(showHelp()));

    //create playbutton
    playButton = new QPushButton (tr("Play"), this);
    playButton->setFont(QFont("Lucida Handwriting",18,QFont::Bold));
    QObject:: connect(playButton,SIGNAL(clicked()),this,SLOT(enterPlayState()));

    //create quitbutton
    quitButton = new QPushButton (tr("Quit"), this);
    quitButton->setFont(QFont("Lucida Handwriting",18,QFont::Bold));

    //set the scene window
    scene->setSceneRect(0,0,600,480);
    scene->setFocus();

    //adding widgets to the scene
    scene->addWidget(playButton);
    scene->addWidget(helpButton);
    scene->addWidget(quitButton);

    //set the Geometry of the widgets
    playButton->setGeometry(200,300,200,50);
    helpButton->setGeometry(200,350,200,50);
    quitButton->setGeometry(200,400,200,50);

    //show the view
    //changeState = false;
    //this->show();

}//end method


void Menu::enterPlayState()
{//start method

    gameObject = new Game(&toplevelScene);
    gameObject->show();
    gameObject->update();

    this->hide();
}//end method

void Menu::showHelp()
{//start help

    QMessageBox trybox;
    trybox.setText("Help Instructions will be shown here");
    trybox.exec();

}//end help

