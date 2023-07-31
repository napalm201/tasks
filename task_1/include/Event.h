#include <stdint.h>


enum class EventType : int8_t {
	UNDEF = 1,
	MOUSE,
	KEYBOARD
};

enum class Action : int8_t {
	PRESS = 1,
	RELEASE
};

enum class MouseButton : int8_t {
	RIGHT = 1,
	LEFT
};

struct Event {

	EventType type;

	Action action;

	union {
	    
		struct Mouse {
			MouseButton button;
			int8_t x;
			int8_t y;
		};

		uint8_t keyboard;

	};
};