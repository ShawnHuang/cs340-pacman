/*****************************************************
  File Name: maploader.h
  Created by: Riddhi Kapasi
  ******************************************************/

#ifndef MAPLOAADER_H
#define MAPLOAADER_H

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QMap>

struct CoordChar //structure used in a list to store coordinates.
{
    int xcoord;
    int ycoord;
    int symbol;
};

class MapLoader : public QFile //Maploader class
{
public:
    MapLoader();
    ~MapLoader();
    void FileRead();

    QMap<QString, CoordChar> map;
    QMap<QString, CoordChar>::iterator it;
    void ListRead();

private:
    QString filename;
    int xcoord;
    int ycoord;
};

#endif // MAPLOAADER_H

