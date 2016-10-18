// Definitions

// MAX_LEDS is the amount of LED lights you're connecting.
#define MAX_LEDS 10

/* LED_OFFSET is the starting pin for the first LED.
   By default I chose MAX_LED 10 (ten LED lights).
   This means the pins 4, 5, 6, 7, 8, 9, 10, 11, 12, 13.
   are gonna be the 10 output pins for LED lights. */
#define LED_OFFSET 4

/* BUTTON_PIN is the pin for button input.
   By default I chose LED_OFFSET - 1. This means the previous
   pin before the first LED is the button input (in default
   case it's pin #3) */
#define BUTTON_PIN (LED_OFFSET - 1)

#if BUTTON_PIN < 0
#error "The BUTTON_PIN is invalid (less than 0), please fix it before compiling."
#endif

// Pattern types
#define PATTERN_FORWARD 0
#define PATTERN_BACKWARD 1
#define PATTERN_PARTICLES 2
#define PATTERN_RED 3
#define PATTERN_YELLOW 4
#define PATTERN_GREEN 5
#define PATTERN_RANDOM 6
#define PATTERN_INVERT 7

// Global Variables
int pattern_mode = PATTERN_FORWARD;		// Pattern Mode
unsigned long previousMillis = 0;		// Millisecond value from last tick
bool button_pressed = false;			// True if button is pressed
LEDLight leds[MAX_LEDS];				// Array of LED objects
int partic_1, partic_2;					// Position values for 2 particles
int timerMillis = 200;					// Millisecond interval between each tick

// Functions
void UpdatePinStates();					// Updates output pin states
void ResetLEDs();						// Toggles all LED lights OFF
void HandleButton();					// Handle voltage received from button pin
void HandleTick();						// Handles timer tick

// These are self-explanatory
void HandlePatternForward();
void HandlePatternBackward();
void HandlePatternParticles();
void HandlePatternColour(int colour);
void HandlePatternRandom();
void HandlePatternInvert();
