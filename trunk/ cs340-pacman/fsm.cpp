/*****************************************************
  File Name: fsm.cpp
  Description: Generic class for saving different states for any individual entity
  Created by: Riddhi Kapasi
  Modified by :
******************************************************/
#include "fsm.h"
#include <qDebug>

FSM::FSM()
{
}

FSM::~FSM()
{
}

void FSM::update()
{
    //qDebug() << "in FSM::update - stateStatus: " << stateStatus;
    if(stateStatus == ENTRY)
        stateStatus = IN;
    else if(stateStatus == EXIT)
    {
//        qDebug() << "in FSM::update - currState: " << currState;
//        qDebug() << "in FSM::update - newState: " << newState;
//        qDebug() << "in FSM::update - prevState: " << prevState;
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

int FSM::getStateIndex()
{
    State s = statemap.value(currState);
    return s.getIndex();
}

bool FSM::hasProperty(QString propertyName)
{
    State s = statemap.value(currState);
    return s.hasProperty(propertyName);
}

void FSM::handleEvent(QString eventName)
{
    //qDebug() << "in FSM::HandleEvent - eventName: " << eventName;
    //qDebug() << "in FSM::HandleEvent - currState: " << currState;
    State s = statemap.value(currState);
    newState = s.getNextStateForEvent(eventName);
    //qDebug() << "in FSM::HandleEvent - newState: " << newState;
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



