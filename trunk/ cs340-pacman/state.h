/*****************************************************
  File Name: state.h
  Description: The state class is responsible for setting transitions, specifying actions, and pointing
               to the right function that represents the action.
  Created by: Riddhi Kapasi
  Modified by :
******************************************************/


#ifndef STATE_H
#define STATE_H

#include <QString>
#include <QMap>
#include <QSet>

//Creating a class state which will contain the name, properties and event mapping of a particular state.
//This is a generic class to be used with every entity in the game.

class State
{
    private:
        QString name;//name of a state
        QSet<QString> property; //properties of a entity in that particular state
        QMap<QString, QString> eventmap;//event and their corresponding next states
        int index;

    public:
        State();
        State(QString);
        State(QString, int);
        ~State();
        QString getName();  //retriving the name of the state
        void setProperty(QString); //setting property for a particular state
        bool hasProperty(QString); //checking if a particular state has this property
        void addEventAndNextState(QString, QString); //adding event and nextstate to map
        QString getNextStateForEvent(QString); //getting next state for the event passed
        int getIndex();
};

#endif // STATE_H
