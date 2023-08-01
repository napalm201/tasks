#include <stdint.h>


enum EventType : int8_t {
	UNDEF = 0,
	MOUSE_PRESS,
	MOUSE_RELEASE,
	KEYBOARD_PRESS,
	KEYBOARD_RELEASE,
    RESIZE
};

enum  MouseButton : int8_t {
	LEFT = 0,
	RIGHT
};

struct Mouse {
	MouseButton button;
	int8_t x;
	int8_t y;
};

struct Event {

	EventType type;

	union {
	    
		Mouse mouse;

		uint8_t keyboard;

	};
};