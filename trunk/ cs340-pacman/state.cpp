/*****************************************************
  File Name: state.cpp
  Description: The state class is responsible for setting transitions, specifying actions, and pointing
                to the right function that represents the action.
  Created by: Riddhi Kapasi
  Modified by :
******************************************************/
#include "state.h"

State::State()
{

}

State::State(QString statename)
{
    name = statename;
}

State::State(QString name, int index)
{
    this->name = name;
    this->index = index;
}


State::~State()
{
}

QString State::getName()
{
    return name;
}

int State::getIndex()
{
    return index;
}

void State::setProperty(QString propertyName)
{
    property.insert(propertyName);
}

bool State::hasProperty(QString propertyName)
{
    return property.contains(propertyName);
}

void State::addEventAndNextState(QString eventName, QString stateName)
{
    eventmap.insert(eventName, stateName);
}

QString State::getNextStateForEvent(QString eventName)
{

    QString v = eventmap.value(eventName);
    return v;
}







