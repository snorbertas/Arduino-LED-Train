#ifndef _LED
#define _LED

// Colour ids
#define RED 0
#define YELLOW 1
#define GREEN 2

/* LED light class. Used specifically for this project,
   but may be used outside as well. Can further expand it
   by adding r, g, b int values, etc. */
class LEDLight
{
public:
	LEDLight();						// Constructor
	void Toggle();					// Inverts state (HIGH to LOW, LOW to HIGH)
	void ToggleOn();				// Toggles state to HIGH
	void ToggleOff();				// Toggles state to LOW
	bool IsOn();					// Returns true if state is HIGH
	void SetColour(int colour);		// Set colour for LED (for group pattern purposes)
	int state = LOW;				// Stores state either as LOW or HIGH (0 or 1)
	int colour = RED;				// Stores colour id
};
#endif