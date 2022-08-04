//
// Created by Dmitry on 25.07.2022.
//

#include "EventManager.h"

void EventManager::subscribe(Event::EventType type, Subscriber *subscriber) {
    if (!subscriber)return;
    auto item = std::find(subscribers[subscriber].begin(), subscribers[subscriber].end(), type);
    if (item == subscribers[subscriber].end()) subscribers[subscriber].push_back(type);
}

void EventManager::publish(Event::EventType type, Event *e) {
    for (auto &pSub: subscribers) {
        if (std::find(pSub.second.begin(), pSub.second.end(), type) != pSub.second.end())pSub.first->update(e);
    }
}

void EventManager::unsubscribe(Event::EventType type, Subscriber *subscriber) {
    if (!subscriber)return;
    auto item = std::find(subscribers[subscriber].begin(), subscribers[subscriber].end(), type);
    if (item != subscribers[subscriber].end()) subscribers[subscriber].erase(item);
}

EventManager &EventManager::getInstance() {
    static EventManager instance;
    return instance;
}

EventManager::~EventManager() {
    // std::cout << "Destructor EventManager (" << this << ") called " << std::endl;
    subscribers.clear();
}

void EventManager::eventRoute(Event *e) {
    auto &manager = EventManager::getInstance();
    if (e->getType() == Event::EventType::MOUSE_BUTTON_PRESSED_EVENT) {
        manager.publish(Event::EventType::MOUSE_BUTTON_PRESSED_EVENT, e);
    }
    if (e->getType() == Event::EventType::MOUSE_MOVED_EVENT) {
        manager.publish(Event::EventType::MOUSE_MOVED_EVENT, e);
    }
    if (e->getType() == Event::EventType::KEY_PRESSED_EVENT) {
        manager.publish(Event::EventType::KEY_PRESSED_EVENT, e);
    }

}

