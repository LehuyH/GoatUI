#include "goatui/component.hpp"
#include "goatui/ui-kit/button.hpp"
#include "goatui/ui-kit/input.hpp"

using namespace std;

Reactive<string> todoList("");
Reactive<string> currentTodo("");

int main(){
	Component app("div",{
		new Attribute("class","flex justify-center flex-col gap-2 h-screen max-w-md mx-auto")
	},{
		new InputText("Enter a todo item",currentTodo),

		new ButtonPrimary("Add Todo Item",{
			EventListener("click",[](int value){
				todoList = todoList.getValue() + "\n" + currentTodo.getValue();
				currentTodo = "";
			})
		}),

		new ButtonDanger("Delete Last",{
			EventListener("click",[](int value){
				string todosStr = todoList.getValue();
				int lastNewline = todosStr.find_last_of("\n");
				todoList = todosStr.substr(0,lastNewline);
			})
		}),

		new Component("p",{
			new Attribute("class","whitespace-pre")
		},{
			new s(todoList)
		})
	});
	app.mount();
}