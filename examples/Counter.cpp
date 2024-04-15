#include "goatui/component.hpp"
using namespace std;

Reactive<int> counter(0);

int main(){
	Component app("div",{
		new Component("button",{
			new Attribute("class","bg-gray-200 hover:bg-gray-100 rounded p-4")
			},{
				EventListener("click",[](int){
					counter = counter.getValue() + 1;
				}),
			},{
				new r("This button has been clicked "), new s(counter), new r(" times")
			}
		)
	});
	app.mount();
}