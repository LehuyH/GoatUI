template <typename T>
class InputText : public Component
{
public:
    InputText(std::string placeholder, Reactive<T>& state ) : Component("input",{
        new Attribute("placeholder",placeholder),
    new Attribute("class","flex h-10 w-full rounded-md border border-gray-200 bg-background px-3 py-2 text-sm ring-offset-background placeholder:text-gray-400 focus-visible:outline-none focus-visible:ring-2 focus-visible:ring-ring focus-visible:ring-offset-2 disabled:cursor-not-allowed disabled:opacity-50"),
        new ReactiveAttribute("value",state)
    },{
        EventListener("change",[&state](int valuePtr){
            state = (std::string((char*)valuePtr));
        })
    }){}
};
