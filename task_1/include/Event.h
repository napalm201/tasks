#include <stdint.h>


enum EventType : int8_t {
	UNDEF = 1,
	MOUSE,
	KEYBOARD
};

enum Action : int8_t {
	PRESS = 1,
	RELEASE
};

enum  MouseButton : int8_t {
	RIGHT = 1,
	LEFT
};

struct Mouse {
	MouseButton button;
	int8_t x;
	int8_t y;
};

struct Event {

	EventType type;

	Action action;

	union {
	    
		Mouse mouse;

		uint8_t keyboard;

	};
};