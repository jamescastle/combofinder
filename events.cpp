#include "dsofinder.h"

//THIS FILE CONTAINS BASIC INFORMATION ON EVENTS AND RELATED ITEMS
//FOR DETAILED ITEM DEFINITIONS SEE items.cpp

DsoFinder::event_data DsoFinder::get_events()
{
    int eventcount = 8;

    event* events = new event[eventcount];

    events[0].caption = tr("None");
    events[0].id = 0;
    events[0].itemcount = 0;

    events[1].caption = tr("Halloween 2013");
    events[1].id = 1;
    events[1].itemcount = 1;

    events[2].caption = tr("Christmas Events");
    events[2].id = 2;
    events[2].itemcount = 3;

    events[3].caption = tr("Easter 2014");
    events[3].id = 3;
    events[3].itemcount = 4;

    events[4].caption = tr("Soccer Events");
    events[4].id = 4;
    events[4].itemcount = 9;

    events[5].caption = tr("Halloween 2014+");
    events[5].id = 5;
    events[5].itemcount = 1;

    events[6].caption = tr("Easter 2015+");
    events[6].id = 6;
    events[6].itemcount = 1;

    events[7].caption = tr("Anniversary 2018");
    events[7].id = 7;
    events[7].itemcount = 2;

    event_data my_events;
    my_events.eventcount = eventcount;
    my_events.events = events;
    return my_events;
}
