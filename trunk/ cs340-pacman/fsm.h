// Class to hold all states for individual characters

#ifndef FSM_H
#define FSM_H

#include <QMap>
#include <QString>


#include "state.h"

enum STATESTATUS
{
    ENTRY = 1,
    IN,
    EXIT
};

class FSM
{
    private:
        QString currState;
        QString newState;
        QString prevState;
        STATESTATUS stateStatus;
        QMap<QString, State> statemap;//map holding state name and state object

    public:
        FSM();
        ~FSM();
        void update();//update nextstate
        void addState(State&);//adding state name and corresponding object in the map
        QString getState();//retriving the name of the state
        bool inENTRY();
        bool inIN();
        bool inEXIT();
        bool hasProperty(QString);//checking if state has tht property,this function will call same function in state.cpp
        void handleEvent(QString);//it gets new state according to the event taken place
        void setInitialState(QString);   //sets initial state
};

#endif // FSM_H
