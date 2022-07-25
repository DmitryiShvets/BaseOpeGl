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
    };
protected:
    EventType type;
    std::string name;
protected:
    Event(const std::string &name, EventType type)
            :
            name(name),
            type(type) {}

public:
    virtual ~Event() = default;

public:
    inline std::string getName() const { return name; }

    inline EventType getType() const { return type; }

    virtual std::string format() const = 0;
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

public:
    std::string format() const override {
        std::string formatted = name + ": " + std::to_string(button);
        return formatted;
    }

};

#endif //BASEOPEGL_EVENTSYSTEM_H
