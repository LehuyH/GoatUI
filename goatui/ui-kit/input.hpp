class InputText : public Component
{
public:
    InputText(std::string placeholder, Reactive<std::string>& state ) : Component("input",{
        new Attribute("placeholder",placeholder),
        new Attribute("type","text"),
    new Attribute("class","flex h-10 w-full rounded-md border border-gray-200 bg-background px-3 py-2 text-sm ring-offset-background placeholder:text-gray-400 focus-visible:outline-none focus-visible:ring-2 focus-visible:ring-ring focus-visible:ring-offset-2 disabled:cursor-not-allowed disabled:opacity-50"),
        new ReactiveAttribute("value",state)
    },{
        EventListener("change",[&state](int valuePtr){
            state = (std::string((char*)valuePtr));
        })
    }){}
};

class InputNumber : public Component
{
public:
    InputNumber(std::string placeholder, Reactive<double>& state ) : Component("input",{
        new Attribute("placeholder",placeholder),
        new Attribute("type","number"),
    new Attribute("class","flex h-10 w-full rounded-md border border-gray-200 bg-background px-3 py-2 text-sm ring-offset-background placeholder:text-gray-400 focus-visible:outline-none focus-visible:ring-2 focus-visible:ring-ring focus-visible:ring-offset-2 disabled:cursor-not-allowed disabled:opacity-50"),
        new ReactiveAttribute("value",state)
    },{
        EventListener("change",[&state](int valuePtr){
            std::string value = (std::string((char*)valuePtr));
            state = std::stod(value);
        })
    }){}
};


class InputCheckbox : public Component
{
public:
    InputCheckbox(std::string label, Reactive<bool>& state ) : Component("input",{
        new Attribute("type","checkbox"),
        new Attribute("class","h-4 w-4 rounded border-gray-300 text-indigo-600 focus:ring-indigo-500 focus:border-indigo-500 sm:text-sm"),
        new ReactiveAttribute("checked",state)
    },{
        EventListener("change","target.checked",[&state](int valuePtr){
            state = valuePtr;
        })
    }){
        this->children.push_back(new r(label.c_str()));
    }
};

class InputTextArea : public Component
{
public:
    InputTextArea(std::string placeholder, Reactive<std::string>& state ) : Component("textarea",{
        new Attribute("placeholder",placeholder),
        new Attribute("class","flex h-10 w-full rounded-md border border-gray-200 bg-background px-3 py-2 text-sm ring-offset-background placeholder:text-gray-400 focus-visible:outline-none focus-visible:ring-2 focus-visible:ring-ring focus-visible:ring-offset-2 disabled:cursor-not-allowed disabled:opacity-50"),
        new ReactiveAttribute("value",state)
    },{
        EventListener("change",[&state](int valuePtr){
            state = (std::string((char*)valuePtr));
        })
    }){}
};