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

{
counter = 0;
    this->resize(640,480);
    this->setBackgroundBrush(QPixmap("../images/display.gif"));

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
    playButton->setGeometry(225,300,200,50);
    helpButton->setGeometry(225,350,200,50);
    quitButton->setGeometry(225,400,200,50);
    intro->play();
}

void Menu::enterPlayState()
{
    gameObject = new Game(&toplevelScene);
    gameObject->show();
    this->hide();
}

void Menu::showHelp()
{
    QMessageBox trybox;
    trybox.setText("Use the arrow keys to manuover Pacman around the maze\n complete the level by eating all the dots. Avoid the ghost,\n if they catch you you will lose a life. Eat the power dot(big dots),\n and the monsters will temporarily turn blue, meaning that\n you can now eat them.");
    trybox.exec();
}

