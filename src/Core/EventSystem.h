//
// Created by Dmitry on 24.07.2022.
//

#ifndef BASEOPEGL_EVENTSYSTEM_H
#define BASEOPEGL_EVENTSYSTEM_H


#include <string>

class Event {
public:
    enum class EventType {
        MOUSE_MOVED_EVENT = 1,
        MOUSE_SCROLLED_EVENT,
        MOUSE_BUTTON_PRESSED_EVENT,
        MOUSE_BUTTON_RELEASED_EVENT,
        KEY_PRESSED_EVENT,
        KEY_RELEASED_EVENT,
        KEY_REPEATED_EVENT,
        WINDOW_RESIZED_EVENT,
        WINDOW_CLOSED_EVENT,
        NODE_SELECTED_EVENT,
        NODE_UNSELECTED_EVENT,
        MOVE_FIGURE_EVENT,
        GAME_END_EVENT,
        GAME_PAUSED_EVENT
    };
protected:
    EventType type;
    std::string name;
protected:
    Event(const std::string &name, EventType type) : name(name), type(type) {}

public:
    virtual ~Event() = default;

public:
    inline std::string getName() const { return name; }

    inline EventType getType() const { return type; }


};

class MouseMovedEvent : public Event {
public:
    MouseMovedEvent(int x, int y)
            :
            Event("Mouse moved Event", Event::EventType::MOUSE_MOVED_EVENT),
            x(x),
            y(y) {}

    int x, y;

};

class MouseButtonPressedEvent : public Event {
public:
    int button;
    double x;
    double y;

public:
    MouseButtonPressedEvent(int button, double x, double y)
            :
            Event("Mouse button pressed", Event::EventType::MOUSE_BUTTON_PRESSED_EVENT),
            button(button), x(x), y(y) {}


};

class KeyPressedEvent : public Event {
public:
    int key;
public:
    KeyPressedEvent(int key) : Event("Key Pressed Event", Event::EventType::KEY_PRESSED_EVENT), key(key) {}


};

class NodeSelectedEvent : public Event {
public:
    NodeSelectedEvent(const std::string &nodeName) : Event("Node Selected Event", Event::EventType::NODE_SELECTED_EVENT), nodeName(nodeName) {}

    ~NodeSelectedEvent() override = default;

    std::string nodeName;
};

class NodeUnselectedEvent : public Event {
public:
    NodeUnselectedEvent(const std::string &nodeName) : Event("Node Unselected Event", Event::EventType::NODE_UNSELECTED_EVENT), nodeName(nodeName) {}

    ~NodeUnselectedEvent() override = default;

    std::string nodeName;
};

class MoveFigureEvent : public Event {
public:
    MoveFigureEvent(const std::string &src, const std::string &dist) : Event("Move Figure Event", Event::EventType::MOVE_FIGURE_EVENT),
                                                                       srcNodeName(src), distNodeName(dist) {}

    ~MoveFigureEvent() override = default;

    std::string srcNodeName;
    std::string distNodeName;
};

class GameEndEvent : public Event {
public:
    GameEndEvent(std::string _result, std::string _comment) : Event("Move Figure Event", Event::EventType::GAME_END_EVENT),
                                                              result(std::move(_result)), comment(std::move(_comment)) {}

    ~GameEndEvent() override = default;

    std::string result;
    std::string comment;

};

class GamePausedEvent : public Event {
public:
    GamePausedEvent(bool status) : Event("Move Figure Event", Event::EventType::GAME_PAUSED_EVENT), status(status) {}

    ~GamePausedEvent() override = default;

    bool status;

};


#endif //BASEOPEGL_EVENTSYSTEM_H
