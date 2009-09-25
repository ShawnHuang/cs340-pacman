#include "MyButtons.h"
#include<QtGui>

MyButtons::MyButtons(QWidget *parent)
        :QWidget(parent)
{
    //creating three buttons that will be the beginning menu display after splash screen.
    help_Button = new QPushButton("Help!");
    play_Button = new QPushButton("Play Game");
    quit_Button = new QPushButton("Quit");

    //This will be the window for our layout screen for widgets/buttons
    QVBoxLayout *layout= new QVBoxLayout;

    //start connecting signals and slots. If user clicks help, message pops up
    QObject:: connect(help_Button, SIGNAL(clicked()),this, SLOT(displayInstructions()));
    //if user clicks quit, exit the application
    QObject:: connect(quit_Button,SIGNAL(clicked()),this,SLOT(close()));

    //QGraphicsScene *scene;
    //Add the buttons to the window
    layout->addWidget(play_Button);
    layout->addWidget(help_Button);
    layout->addWidget(quit_Button);
    setLayout(layout);
    setWindowTitle(tr("PACMAN Game"));
    QPixmap pix("C:/Users/Ali/Desktop/pacmanmenu.png");
    //scene->addPixmap(pix);
}
//The following function displays the instructions when the client clicks the help
//button. If the quit button is clicked, then the game exits.
void MyButtons::displayInstructions()
{
    QMessageBox msgBox;
    //msgBox.setTextFormat(Qt::RichText);
    msgBox.setText("Instructions:\n\nPlay the game by moving your yellow Pac-Man around the board to eat the white dots. You finish the round when you clear the board of all the white dots. Higher levels release the ghosts faster, adding to the excitement of the game!\n\nWatch out for the ghosts! If they eat your Pac-Man, then you lose a life. The game continues until you run out of lives.\n\nEarn extra points by eating the fruit that sometimes appears on the screen. Eat the power pills, and gobble up those ghosts before they eat you.");
    msgBox.exec();
 }

