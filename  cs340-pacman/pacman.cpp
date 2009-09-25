#include "pacman.h"
#include <QtGui>
#include<QGraphicsScene>
#include<QPainter>
#include<QStyleOption>

Pacman::Pacman(){
     x=0;
     y=0;
    colorOfPacman = QColor(255,255,0,255);
    playState =true;
    deadState =false;
    powerfulState =false;
}

 QRectF Pacman::boundingRect() const
 {
     qreal adjust = 0.5;
     return QRectF(-18 - adjust, -22 - adjust,
                   36 + adjust, 60 + adjust);
 }

void Pacman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter ->setBrush(colorOfPacman);
    painter->drawPie(80, 80, 40, 40, 70 * 12, 270 * 16);  //drawing pacman body
    painter->drawPoint(100,90);  //drawing eye
    painter->drawPoint(101,90);
    //painter->drawPoint(99,90);
   //ainter->drawPoint(98,90);
}
//bool Pacman:: checkMove(int newX, int newY){
   // if(main->wall->isWall(newX, newY)) return false;
  //  else
       // return true;
//}

void Pacman::moveXdirection(int newX){
    x= newX;
}

void Pacman::moveYdirection(int newY){
    y=newY;
}

int Pacman::getX(){
    return x;
}
int Pacman::getY(){
    return y;
}

//void setState(bool someState){
  //  if(someState==playState){health = 100;deadState =false;powerfulState = false;}
    //if(someState==deadState){playState =false;powerfulState=false;health=0;}
    //if(someState==powerfulState){playState = false; deadState=false;
//}
