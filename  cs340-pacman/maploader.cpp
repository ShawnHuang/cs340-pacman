/*****************************************************
  File Name: maploader.cpp
  Description: Reads the text file and stores the coordinated of the char'+' in a list
  Created by: Riddhi Kapasi
  Modified by:
******************************************************/

#include "maploader.h"

MapLoader::MapLoader() //constructor
{
    xcoord = 0;
    ycoord = 0;
}

MapLoader::~MapLoader() //destructor
{
}

void MapLoader::FileRead() //reads the text file, looks for '+' char, stores its co ordinates in a list.
{

     QFile file("in.txt"); // Qfile file = new QFile("in.txt");
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         return;

     CoordChar cc;

     QTextStream in(&file); //QTextStream in = new QTextStream(&file);
     while (!in.atEnd()) {
         QString line = in.readLine();
         for (int i = 0; i < line.size(); ++i)
         {
            if (line.at(i) == QChar('+'))
            {
                cc.xcoord = xcoord;
                cc.ycoord = ycoord;
                cc.symbol = '+';
                QString *key = new QString(QChar(xcoord + 48));
                key->append(QChar('_')).append(QChar(ycoord + 48));
                map.insert(*key, cc);
            }
            xcoord++;
         }
         ycoord++;
         xcoord = 0;
     }
}

void MapLoader::ListRead()  // Testing function to print the list value
{
    int a;
    int b;

    for(it = map.begin(); it != map.end(); it++)
    {
        a = it->xcoord;
        b = it->ycoord;
    }
}
