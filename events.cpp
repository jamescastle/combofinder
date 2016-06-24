#include "dsofinder.h"

//THIS FILE CONTAINS BASIC INFORMATION ON EVENTS AND RELATED ITEMS
//FOR DETAILED ITEM DEFINITIONS SEE items.cpp

void DsoFinder::init_events(QString language)
{
    eventcount = 7;

    events = new event[eventcount];
    i=0;

    events[0].caption = "None";
    events[0].id = 0;
    events[0].itemcount = 0;

    events[1].caption = "Halloween 2013";
    events[1].id = 1;
    events[1].itemcount = 1;

    events[2].caption = "Christmas Events";
    events[2].id = 2;
    events[2].itemcount = 3;

    events[3].caption = "Easter 2014";
    events[3].id = 3;
    events[3].itemcount = 4;

    events[4].caption = "Soccer Events";
    events[4].id = 4;
    events[4].itemcount = 9;

    events[5].caption = "Halloween 2014+";
    events[5].id = 5;
    events[5].itemcount = 1;

    events[6].caption = "Easter 2015+";
    events[6].id = 6;
    events[6].itemcount = 1;

    if (language=="deutsch")
    {
        events[0].caption = "Kein Event";
        events[2].caption = "Weihnachtsevents";
        events[3].caption = "Ostern 2014";
        events[4].caption = "Fußballevents";
        events[6].caption = "Ostern 2015+";
    }
    else
    {
        return;
    }
}
