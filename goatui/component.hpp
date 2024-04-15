#include<string>
#include<vector>
#include <emscripten/emscripten.h>
#include "./reactive.hpp"
#include "./event.hpp"

class Attribute{
    private:
    std::string key;
    std::string value;
    public:
    Attribute(std::string key){
        this->key = key;
        this->value = "";
    }
    Attribute(std::string key,std::string value){
        this->key = key;
        this->value = value;
    }

    std::string getKey() const{
        return this->key;
    }

    std::string getValue() const{
        return this->value;
    }

    virtual std::string render(){
        return this->key + "=\"" + this->value + "\"";
    }
};

template <typename T>
class ReactiveAttribute: public Attribute{
    private:
    std::string reactiveID;
    public:
    ReactiveAttribute(std::string key,Reactive<T>& reactive) : Attribute(key){
        this->reactiveID = reactive.getID();
    }

    std::string render() override{
        return "v-bind:" + this->getKey() + "=\"" + this->reactiveID + "\"";
    }
};


class Component
{
protected:
    std::string elementName;
    std::vector<Component*> children;
    std::vector<Attribute*> attributes;
    std::vector<EventListener> eventListeners;

public:
    Component(){
        this->elementName = "raw";
    }
    Component(std::string& elementName){
        this->elementName = elementName;
        this->children = std::vector<Component*>();
        this->attributes = std::vector<Attribute*>();
    }

    Component(std::string elementName){
        this->elementName = elementName;
        this->children = std::vector<Component*>();
        this->attributes = std::vector<Attribute*>();
    }

    Component(std::string elementName,std::vector<Component*>& children){
        this->elementName = elementName;
        this->children = std::vector<Component*>();
        this->children = children;
        this->attributes = std::vector<Attribute*>();
    }

    Component(std::string elementName,std::vector<Component*> children){
        this->elementName = elementName;
        this->children = std::vector<Component*>();
        this->children = children;
        this->attributes = std::vector<Attribute*>();
    }

    Component(std::string elementName,std::vector<Attribute*> attributes){
        this->elementName = elementName;
        this->children = std::vector<Component*>();
        this->attributes = std::vector<Attribute*>();
        this->attributes = attributes;
    }

    Component(std::string elementName,std::vector<Attribute*> attributes,std::vector<Component*>& children){
        this->elementName = elementName;
        this->attributes = attributes;
        this->children = std::vector<Component*>();
        this->children = children;
    }

    Component(std::string elementName,std::vector<Attribute*> attributes,std::vector<Component*> children){
        this->elementName = elementName;
        this->attributes = std::vector<Attribute*>();
        this->attributes = attributes;
        this->children = std::vector<Component*>();
        this->children = children;
    }

    Component(std::string elementName,std::vector<EventListener> eventListeners){
        this->elementName = elementName;
        this->children = std::vector<Component*>();
        this->eventListeners = eventListeners;
    }

    Component(std::string elementName,std::vector<Attribute*> attributes,std::vector<EventListener> eventListeners){
        this->elementName = elementName;
        this->attributes = std::vector<Attribute*>();
        this->attributes = attributes;
        this->children = std::vector<Component*>();
        this->eventListeners = eventListeners;
    }

    Component(std::string elementName,std::vector<EventListener> eventListeners, std::vector<Component*> children){
        this->elementName = elementName;
        this->children = std::vector<Component*>();
        this->children = children;
        this->eventListeners = eventListeners;
    }

    Component(std::string elementName,std::vector<Attribute*> attributes,std::vector<EventListener> eventListeners, std::vector<Component*> children){
        this->elementName = elementName;
        this->attributes = std::vector<Attribute*>();
        this->attributes = attributes;
        this->children = std::vector<Component*>();
        this->children = children;
        this->eventListeners = eventListeners;
    }

    virtual std::string render(){
        std::string eventListeners = "";
        for(EventListener eventListener : this->eventListeners){
            if(eventListener.getEventKey() == "change"){
                eventListeners += "@input=\"callEventListenerWithValue($event.target.value," + std::to_string(eventListener.getId()) + ")\"";
            }else{
                eventListeners += "@" + eventListener.getEventKey() + "=\"_callEventListener(" + std::to_string(eventListener.getId()) + ")\"";
            }
        }

        std::string attributes = "";
        for(Attribute* attribute : this->attributes){
            attributes += attribute->render() + "\n";
        }

        std::string templateHTML = (this->elementName != "raw") ?  ("<" + this->elementName + " " +  attributes + "\n" + eventListeners + ">\n") : "";

        for(Component* child : this->children){
            templateHTML+= child->render();
        }

        if(this->elementName != "raw") templateHTML+="</" + this->elementName + ">";

        return templateHTML;
    }


    void mount(){
        std::string templateHTML = this->render();
        MAIN_THREAD_EM_ASM({
            document.body.innerHTML = UTF8ToString($0);
            mount();
        },templateHTML.c_str());
        return;
    }    
};;

// renders a string
class r: public Component{
    private:
    std::vector<Readable> textContent;

    public:
    r(std::vector<Readable>& textContent){
        this->textContent = textContent;
    }

    r(std::vector<Readable> textContent){
        this->textContent = textContent;
    }

    r(Readable& textContent){
        this->textContent = std::vector<Readable>({textContent});
    }

        r(Readable textContent){
           this->textContent = std::vector<Readable>({textContent});
        }

        r(std::string text){
            Readable readable(text);
            this->textContent = std::vector<Readable>({readable});
        }
        
    virtual std::string render() override{
        std::string htmlTemplate = "";
        for(Readable text : textContent){
            htmlTemplate += text.getReadValue();
        }
        return htmlTemplate;
    }

};

// renders the value of a reactive variable
template <typename T>
class s: public Component{
    private:
    Reactive<T> reactive;

    public:
    s(Reactive<T>& reactive){
        this->reactive = reactive;
    }

    virtual std::string render() override{
        return this->reactive.getReadValue();
    }

};