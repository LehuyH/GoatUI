#  GoatUI 🐐
[![Run on Replit](https://replit.com/badge)](https://replit.com/@LehuyH/GoatUI-Starter)

*It's React... but for C++!*


GoatUI is a C++ library that allows you to create web-based user interfaces using components. It compiles your C++ code into WebAssembly, which runs in the browser to generate the UI.

## Why Use GoatUI?

 
-  **Web-Based:** Create interactive user interfaces that run in the browser using C++.

- **Cross-Platform:** With WebAssembly, your GoatUI program can run across all modern browsers.

-  **Reactive Components:** Build your UI using components that automatically update when the state changes.

- **Event Handling:** Handle events like button clicks and form submissions with ease.

  

## 🛠️ Installation

  

### Prerequisites

1.  **Emscripten:** Install [Emscripten](https://emscripten.org/docs/getting_started/downloads.html) to compile C++ to WebAssembly.

  

### Steps

  

1.  **Clone the Repository:**  `git clone https://github.com/LehuyH/goatui.git`

2.  **Include `goatui/component.hpp`:** Add `#include "goatui/component.hpp"` in your C++ project.

  
## 🚀 Quick Start Example

```cpp
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
```

Outputs the following:
![Quick Start Example](/.github/quickstart.png)

## 🧰 Usage

GoatUI provides an easy-to-use API for creating web-based user interfaces using C++. Here's a quick overview of the main concepts:

### Components
Use the `Component` class to create UI elements. Each component can have children components, attributes, and event listeners.

```cpp
Component(string HTMLTag, vector<Attribute*> attributes, vector<EventListener*> eventListeners, vector<Component*> children)
```
You can omit `attributes`, `eventListeners`, or `children` but the order must be preserved.

Here's an example of a simple component:

```cpp
Component container("div", {
	new Attribute("class", "flex items-center flex-col justify-center min-h-screen p-8 space-y-4")
}, {
	// You can nest components inside other components
	new Component("h1", {
		// Add attributes to the component
		new Attribute("class", "text-2xl")
	}, {
		new r("Hello, World!")
	}),
	new Component("button", {
		new Attribute("class", "bg-blue-500 text-white p-2 rounded")
	}, {
		// Add event listeners to the component
		EventListener("click", [](int) {
			// Handle the event here
		})
	}, {
		new r("Click me!")
	})
});
```

To render the component, call the `mount` method:

```cpp
container.mount();
```

This will render the GUI in the browser:
![Component Example](/.github/comp.png)

By default, GoatUI's web executor includes [UnoCSS](https://unocss.dev/) with a TailwindCSS compatibility layer for styling. This means you can use any class from TailwindCSS to style your components.

However, this behavior can be modified by changing `./dist/index.html` to include your own CSS file.

#### Utility Components
You can use the `r` class to render raw text and the `s` class to render reactive values
  
  ```cpp
  new Component("h1",{
    new r("Hello, World! The count is:"),
    new s(counter)
  });
```

### Reactivty
With GoatUI's reactivty system, you can declarative create GUIs that automatically update when the state changes.

To create a reactive value, use the `Reactive` class:

```cpp
Reactive<int> counter(0);
Reactive<string> message("Hello, World!");
```

You can access the value of a reactive variable using the `getValue` method:

```cpp
int value = counter.getValue();
```

To update the value of a reactive variable, simply assign a new value to it:

```cpp
counter = 42;
```

When a reactive variable is updated, any components that depend on it will automatically re-render. 


To specify this relationship, you can use the `s` class to create reactive components.

For example:
```cpp
Component app("div",{
  new Component("h1",{
    new s(counter)
  })
});
```

When the `counter` value changes, the `h1` element will automatically update to reflect the new value.

You can use `ReactiveAttribute` to create reactive attributes too:

```cpp
Reactive<string> inputValue("");

Component input("input",{
  new ReactiveAttribute("value",inputValue)
});
```
This will create an input element that updates its value whenever `inputValue` changes.

### Event Handling
You can handle events like button clicks and form submissions using the `EventListener` class.

The `EventListener` class takes an event name and a callback function as arguments:
```cpp
EventListener(string HTMLEvent, function<void(int)> callback)
```
The callback function takes an integer argument, which is a pointer to the value of the event.



```cpp
Reactive<string> inputValue("");

Component input("input",{
  new ReactiveAttribute("value",inputValue)
},{
  EventListener("input",[](int valuePtr){
    //When the user types in the input, update the reactive value
    inputValue = std::string((char*)valuePtr);
  })
});
```

This code creates an input element that updates the `inputValue` reactive variable whenever the user types in the input.

## 🎨 UI Kit
To improve convenience and reusability, it is recommended to create custom components by deriving from the `Component` class. This allows you to encapsulate common components that you use frequently.

We ship GoatUI with a standard UI kit that includes common components like buttons and inputs under `goatui/ui-kit`.

### `goatui/ui-kit/button.hpp`
Styled button component with hover and active states.

Example with `ButtonPrimary`:
```cpp
ButtonPrimary button("Click me!",[](int){
  //Handle button click
});
```

### `goatui/ui-kit/input.hpp`
A collection of styled input components.

Example with `InputText`:
```cpp
Reactive<string> inputValue("");
InputText("Type something",inputValue);
```


## 🔨 Build

To compile and build your C++ code with GoatUI, follow these steps:

1. Run the following command in your terminal:

```sh
em++ (ADD SOURCE FILES HERE) -s WASM=1 -o ./dist/main.js -s EXPORTED_RUNTIME_METHODS='[\"getValue\",\"ccall\"]' -s NO_EXIT_RUNTIME=1 -s DEFAULT_LIBRARY_FUNCS_TO_INCLUDE='$stringToNewUTF8' -sASYNCIFY -Wno-non-pod-varargs -s EXPORTED_FUNCTIONS=[\"_callEventListener\",\"_callEventListenerWithValue\"] -fexceptions
```

Replace `(ADD SOURCE FILES HERE)` with any additional source files your project requires ex: `main.cpp`

2. This command will generate the necessary output in the `./dist` directory.

3. You can then upload the contents of the `./dist` folder to any static hosting service to run your application.

## 📜 License

GoatUI is licensed under the [MIT License](LICENSE).