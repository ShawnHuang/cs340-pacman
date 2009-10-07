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

State::~State()
{
}

QString State::getName()
{
    return name;
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
    return eventmap.value(eventName);
}







