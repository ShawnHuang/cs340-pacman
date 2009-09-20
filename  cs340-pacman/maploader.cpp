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
                list.push_back(cc);
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

    for(it = list.begin(); it != list.end(); it++)
    {
        a = it->xcoord;
        b = it->ycoord;
    }
}
