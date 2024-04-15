# pragma once

#include<string>
#include <emscripten.h>
#include<iostream>
#include<vector>
#include<functional>

class EventListener{
    private:
        std::string eventKey;
        unsigned int id;
        std::function<void(int)> eventPerformed;
        static int totalListeners;
    public:
        EventListener(std::string key,std::function<void(int)> event);
        void triggerEvent(int value){
            this->eventPerformed(value);
        }
        int getId() const{
            return this->id;
        }
        std::string getEventKey() const{
            return this->eventKey;
        }

};

int EventListener::totalListeners = 0;

EMSCRIPTEN_KEEPALIVE
std::vector<EventListener> hooks;

EventListener::EventListener(std::string key,std::function<void(int)> event){
        totalListeners++;
        this->eventKey = key;
        this->eventPerformed = event;
        hooks.push_back(*this);
        this->id = totalListeners -1;
}

extern "C" {
    EMSCRIPTEN_KEEPALIVE
    void callEventListener(int id){
        hooks.at(id).triggerEvent(0);
    }

    EMSCRIPTEN_KEEPALIVE
    void callEventListenerWithValue(int id, int value){
        hooks.at(id).triggerEvent(value);
    }
}