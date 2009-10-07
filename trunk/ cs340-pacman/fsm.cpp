/*****************************************************
  File Name: fsm.cpp
  Description: Generic class for saving different states for any individual entity
  Created by: Riddhi Kapasi
  Modified by :
******************************************************/
#include "fsm.h"

FSM::FSM()
{
}

FSM::~FSM()
{
}

void FSM::update()
{
    if(stateStatus == ENTRY)
        stateStatus = IN;
    else if(stateStatus = EXIT)
    {
        prevState = currState;
        currState = newState;
        stateStatus = ENTRY;
    }
}

void FSM::addState(State &stateObject)
{
    QString stateName = stateObject.getName();
    statemap.insert(stateName,stateObject);
}

QString FSM::getState()
{
    State s = statemap.value(currState);
    return s.getName();
}

bool FSM::hasProperty(QString propertyName)
{
    State s = statemap.value(currState);
    return s.hasProperty(propertyName);
}

void FSM::handleEvent(QString eventName)
{
    State s = statemap.value(currState);
    newState = s.getNextStateForEvent(eventName);
    stateStatus = EXIT;
}

void FSM::setInitialState(QString name)
{
    currState = name;
    stateStatus = ENTRY;
}

bool FSM::inENTRY()
{
    if(stateStatus == ENTRY)
        return true;
    else
        return false;
}

bool FSM::inIN()
{
    if(stateStatus == IN)
        return true;
    else
        return false;
}

bool FSM::inEXIT()
{
    if(stateStatus == EXIT)
        return true;
    else
        return false;
}



