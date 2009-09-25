#include <QApplication>
#include "MyButtons.h"
#include <QSplashScreen>
#include <QtGui>
#include <windows.h>

int main(int argc, char *argv[])
{
        QApplication app(argc, argv);
        QGraphicsScene *scene;
        MyButtons *menu = new MyButtons;
        QPixmap pix("C:/Users/Ali/Desktop/pacman.png");
        //make an instance of the splash screen
        QSplashScreen *splash =  new QSplashScreen(pix);
       //Set the splash screen to our picture
        splash->setPixmap(pix);
        //show picture
        splash->show();
        //topRight is the variable used to align the messae
        Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
        //showMessage with desired parameters to acheive a nice message
        splash->showMessage(QObject::tr("Loading Processes..."),topRight,Qt::black);

        app.processEvents();
        Sleep(1000);


        //scene->setSceneRect(-300,-300,600,600);
        MyButtons buttons;
        buttons.setGeometry(100,100,500,300);
        QPalette something;
        //something.setColor(Qt::darkBlue);
        buttons.setBackgroundRole(QPalette::Highlight);
        buttons.show();
        QMainWindow window;
        QWidget ql(&window);
        //ql.setPixmap(pix);
        window.setCentralWidget(&ql);
        //ql.show();
       //Sleep(10000);
    splash->finish(&window);
   //QGraphicsProxyWidget *proxy = scene->addWidget(buttons);
   //menu->show();
    return app.exec();
}
