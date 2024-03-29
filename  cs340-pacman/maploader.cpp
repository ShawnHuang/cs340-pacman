
/*****************************************************
  File Name: maploader.cpp
  Description: Reads the text file and stores the coordinated of the char'+' in a list
  Created by: Riddhi Kapasi
  Modified by:
******************************************************/

#include "maploader.h"
#include<QDebug>

MapLoader::MapLoader() //constructor
{
    xcoord = 0;
    ycoord = 0;
}

MapLoader::~MapLoader() //destructor
{
}

void MapLoader::fileRead(QString filename) //reads the text file, looks for '+' char, stores its co ordinates in a list.
{

     QFile file(filename); // Qfile file = new QFile("in.txt");
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         return;

     CoordChar cc;

     QTextStream in(&file); //QTextStream in = new QTextStream(&file);
     while (!in.atEnd()) {
         QString line = in.readLine();
         for (int i = 0; i < line.size(); ++i)
         {
            QString key = QString::number(xcoord).append(QChar('_')).append(QString::number(ycoord));
            QString *playerKey;
            switch(line.at(i).toAscii())
            {

                case '+':
                        cc.xcoord = xcoord;
                        cc.ycoord = ycoord;
                        cc.symbol = '+';
                        map.insert(key, cc);

                        //Map for player movement
                        cc.xcoord = xcoord*10;
                        cc.ycoord = ycoord*10;
                        playerKey = new QString(QChar(xcoord*10));
                        playerKey->append(QChar('_')).append(QChar(ycoord*10));
                        sceneItemsMap.insert(*playerKey,cc);
                        break;

                case '.':
                        cc.xcoord = xcoord;
                        cc.ycoord = ycoord;
                        cc.symbol = '.';
                        dotmap.insert(key, cc);

                        //Map for player movement
                        cc.xcoord = xcoord*10;
                        cc.ycoord = ycoord*10;
                        playerKey = new QString(QChar(xcoord*10));
                        playerKey->append(QChar('_')).append(QChar(ycoord*10));
                        sceneItemsMap.insert(*playerKey,cc);
                        break;

                case 'O':
                        cc.xcoord = xcoord;
                        cc.ycoord = ycoord;
                        cc.symbol = 'O';
                        powerdotmap.insert(key, cc);

                        //Map for player movement
                        cc.xcoord = xcoord*10;
                        cc.ycoord = ycoord*10;
                        playerKey = new QString(QChar(xcoord*10));
                        playerKey->append(QChar('_')).append(QChar(ycoord*10));
                        sceneItemsMap.insert(*playerKey,cc);
                        break;
            }
            xcoord++;
         }
         ycoord++;
         xcoord = 0;
     }
}




