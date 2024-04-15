#include<string>
#include <emscripten/emscripten.h>

class Readable{
    private:
    std::string readValue;

    public:
    Readable(){}
    Readable(std::string& value){
        this->readValue = value;
    }

    virtual std::string getReadValue(){
        return this->readValue;
    }
};

template <typename T>
class Reactive: public Readable{
    private:
    T value;
    std::string id;

    void registerReactive(){
        char *str = (char*)MAIN_THREAD_EM_ASM_PTR({
            return stringToNewUTF8(createReactive($0))
        }, this->value);
        this->id = std::string(str);
        free(str);
    }

    public:
    Reactive(){}
    Reactive(T& value){
        this->value = value;
        this->registerReactive();
    }

    Reactive(T value){
        this->value = value;
        this->registerReactive();
    }

    T getValue() const{
        return this->value;
    }

    void setValue(T& value){
        this->value = value;
        MAIN_THREAD_EM_ASM({
            setState(UTF8ToString($0),($1))
        },this->id.c_str(),value);
    }

    T operator+(Reactive<T> rightHandValue){
        return this->value + rightHandValue.getValue();
    }

    T operator-(Reactive<T> rightHandValue){
         return this->value - rightHandValue.getValue();
    }

    Reactive<T> operator=(T value){
        this->setValue(value);
        return *this;
    }

    virtual std::string getReadValue() override{
        return "{{ " + this->id + " }}";
    }

    ~Reactive(){};
};
//Version for strings
template<>
class Reactive<std::string>: public Readable{
    private:
    std::string value;
    std::string id;

    void registerReactive(){
        char *str = (char*)MAIN_THREAD_EM_ASM_PTR({
            return stringToNewUTF8(createReactive(UTF8ToString($0)))
        }, this->value.c_str());
        this->id = std::string(str);
        free(str);
    }

    public:
    Reactive(){}
    Reactive(std::string& value){
        this->value = value;
        this->registerReactive();
    }

    Reactive(std::string value){
        this->value = value;
        this->registerReactive();
    }

    std::string getValue() const{
        return this->value;
    }

    std::string getID() const{
        return this->id;
    }

    void setValue(std::string& value){
        this->value = value;
        MAIN_THREAD_EM_ASM({
            setState(UTF8ToString($0),UTF8ToString($1))
        },this->id.c_str(),value.c_str());
    }

    std::string operator+(Reactive<std::string> rightHandValue){
        return this->value + rightHandValue.getValue();
    }

    virtual std::string getReadValue() override{
        return "{{ " + this->id + " }}";
    }
    
    ~Reactive(){};
};