class ButtonPrimary : public Component
{
public:
    ButtonPrimary(std::string label, std::vector<EventListener> eventListeners = {}) : Component("button",{
        new Attribute("class","inline-block rounded border border-indigo-600 bg-indigo-600 px-12 py-3 text-sm font-medium text-white hover:bg-transparent hover:text-indigo-600 focus:outline-none focus:ring active:text-indigo-500")
    },eventListeners)
    {
        this->children.push_back(new r(label.c_str()));
    }
};

class ButtonSecondary : public Component
{
public:
    ButtonSecondary(std::string label, std::vector<EventListener> eventListeners = {}) : Component("button",{
        new Attribute("class","inline-block rounded border border-gray-600 bg-gray-600 px-12 py-3 text-sm font-medium text-white hover:bg-transparent hover:text-gray-600 focus:outline-none focus:ring active:text-gray-500")
    },eventListeners)
    {
        this->children.push_back(new r(label.c_str()));
    }
};

class ButtonSuccess : public Component
{
public:
    ButtonSuccess(std::string label, std::vector<EventListener> eventListeners = {}) : Component("button",{
        new Attribute("class","inline-block rounded border border-green-600 bg-green-600 px-12 py-3 text-sm font-medium text-white hover:bg-transparent hover:text-green-600 focus:outline-none focus:ring active:text-green-500")
    },eventListeners)
    {
        this->children.push_back(new r(label.c_str()));
    }
};

class ButtonDanger : public Component
{
public:
    ButtonDanger(std::string label, std::vector<EventListener> eventListeners = {}) : Component("button",{
        new Attribute("class","inline-block rounded border border-red-600 bg-red-600 px-12 py-3 text-sm font-medium text-white hover:bg-transparent hover:text-red-600 focus:outline-none focus:ring active:text-red-500")
    },eventListeners)
    {
        this->children.push_back(new r(label.c_str()));
    }
};

class ButtonWarning : public Component
{
public:
    ButtonWarning(std::string label, std::vector<EventListener> eventListeners = {}) : Component("button",{
        new Attribute("class","inline-block rounded border border-yellow-600 bg-yellow-600 px-12 py-3 text-sm font-medium text-white hover:bg-transparent hover:text-yellow-600 focus:outline-none focus:ring active:text-yellow-500")
    },eventListeners)
    {
        this->children.push_back(new r(label.c_str()));
    }
};