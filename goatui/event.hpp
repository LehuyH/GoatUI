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
        std::string valuePath = "target.value";
    public:
        EventListener(std::string key,std::function<void(int)> event);
        EventListener(std::string key,std::string valuePath,std::function<void(int)> event);

        void triggerEvent(int value){
            this->eventPerformed(value);
        }
        int getId() const{
            return this->id;
        }
        std::string getEventKey() const{
            return this->eventKey;
        }
        std::string getValuePath() const{
            return this->valuePath;
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

EventListener::EventListener(std::string key,std::string valuePath,std::function<void(int)> event){
        totalListeners++;
        this->eventKey = key;
        this->eventPerformed = event;
        this->valuePath = valuePath;
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