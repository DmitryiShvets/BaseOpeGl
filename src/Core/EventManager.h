//
// Created by Dmitry on 25.07.2022.
//

#ifndef BASEOPEGL_EVENTMANAGER_H
#define BASEOPEGL_EVENTMANAGER_H

#include "Subscriber.h"
#include "EventSystem.h"
#include <map>

class EventManager {
public:

    static EventManager &getInstance();

    void subscribe(Event::EventType type, Subscriber *subscriber);

    void publish(Event::EventType type, Event *e);

    void unsubscribe(Event::EventType type, Subscriber *subscriber);

    EventManager(const EventManager &) = delete;

    EventManager &operator=(const EventManager &) = delete;

    ~EventManager();

private:
    EventManager() = default;

    std::map<Subscriber *, std::list<Event::EventType>> subscribers;
};


#endif //BASEOPEGL_EVENTMANAGER_H
