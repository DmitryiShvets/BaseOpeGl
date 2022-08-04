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

class MouseMovedEvent : public Event {
public:
    MouseMovedEvent(int x, int y)
            :
            Event("Mouse moved Event", Event::EventType::MOUSE_MOVED_EVENT),
            x(x),
            y(y) {}

    int x, y;

public:
    std::string format() const override {
        std::string formatted = name + ": " + std::to_string(x) + ", " + std::to_string(y);
        return formatted;
    }
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

class KeyPressedEvent : public Event {
public:
    int key;
public:
    KeyPressedEvent(int key)
            :
            Event("Key Pressed Event", Event::EventType::KEY_PRESSED_EVENT),
            key(key) {}

public:
    std::string format() const override {
        std::string formatted = name + ": " + (char) key;
        return formatted;
    }
};

#endif //BASEOPEGL_EVENTSYSTEM_H
