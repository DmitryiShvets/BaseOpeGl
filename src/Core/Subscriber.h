//
// Created by Dmitry on 25.07.2022.
//

#ifndef BASEOPEGL_SUBSCRIBER_H
#define BASEOPEGL_SUBSCRIBER_H

#include "list"

#include "EventSystem.h"


class Subscriber {
public:

    Subscriber() = default;

    virtual ~Subscriber() {};

    virtual void update(Event *e) = 0;

};

#endif //BASEOPEGL_SUBSCRIBER_H
