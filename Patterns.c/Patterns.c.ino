#include "LED.h"
#include "Patterns.h"

void setup() {
	// Initiate button pin as input mode
	pinMode(BUTTON_PIN, INPUT);
	
	// Initiate LED lights
	for(int i = 0; i < MAX_LEDS; i++){
		// Set pin mode as output for each LED.
		pinMode(i + LED_OFFSET, OUTPUT);
		
		/* Set LED colours
		   This is used to group the LEDs according to their physical colour.
		   You may change this according to your preference/physical arrangement. */
		int colour = i;
		while(colour > GREEN){
			/* Colours beyond green get bumped back by 3 units until they're within 0 - 2 range.
			   This only suits if you're using the same arrangement as mine:
					R, Y, G, R, Y, G, R, Y, G, R
			   If this algorithm doesn't fit your arrangement, you may construct one line by line:
					leds[0].colour = RED;
					leds[1].colour = RED;
					leds[2].colour = GREEN;
					leds[3].colour = YELLOW;
			   Hope that makes sense. */
			colour -= (GREEN + 1);
		}
		leds[i].colour = colour;
	}
	leds[0].ToggleOn();
}

void loop() {
	// Get current milliseconds time.
	unsigned long currentMillis = millis();
	
	/* Read our analog sensor and convert it to max 500ms.
	   We are storing the resulting value as our millesond timer. */
	int sensorValue = analogRead(0);
	timerMillis = (sensorValue/1023.0) * 500;
	
	// Handle voltage received from button pin.
	HandleButton();
	
	// Handle tick (timer).
	if(previousMillis + timerMillis < currentMillis){
		// Remember this as our previous tick.
		previousMillis = currentMillis;
		
		// Handle the patterns.
		HandleTick();
	}
	
	// Update output pin states.
	UpdatePinStates();
}

void UpdatePinStates(){
	// Update states for pins.
	for(int i = 0; i < MAX_LEDS; i++){
		digitalWrite(i + LED_OFFSET, leds[i].state);
	}
}

void ResetLEDs(){
	// Loop trough all LED objects and toggle them off.
	for(int i = 0; i < MAX_LEDS; i++){
		leds[i].ToggleOff();
	}
}

void HandleButton(){
	if(digitalRead(BUTTON_PIN) == HIGH){
		if(button_pressed == false){
			// Button is pressed.
			button_pressed = true;
			
			// Increment pattern mode.
			pattern_mode++;
			
			// Reset pattern mode back to start if exceeding last mode.
			if(pattern_mode > PATTERN_INVERT){
				pattern_mode = PATTERN_FORWARD;
			}
			
			/* If reset back to start, turn off all LED lights and
			   toggle first one ON. */
			if(pattern_mode == PATTERN_FORWARD){
				ResetLEDs();
				leds[0].ToggleOn();
			}
			
			// Initiate particle mode.
			if(pattern_mode == PATTERN_PARTICLES){
				for(int i = 0; i < MAX_LEDS; i++){
					if(leds[i].IsOn()){
						// Set particle locations.
						partic_1 = i;
						partic_2 = i;
					}
				}
			}
			
			// If in colour mode (aka "group" mode), toggle all LEDs OFF.
			if(pattern_mode >= PATTERN_RED && pattern_mode < PATTERN_INVERT){
				ResetLEDs();
			}
		}
	} else {
		// No voltage received, thus button is no longer pressed.
		button_pressed = false;
	}
}

void HandleTick(){	
	// Handle the patterns according to current mode.
	if(pattern_mode == PATTERN_FORWARD){
		HandlePatternForward();
	} else if(pattern_mode == PATTERN_BACKWARD){
		HandlePatternBackward();
	} else if(pattern_mode == PATTERN_PARTICLES){
		HandlePatternParticles();
	} else if(pattern_mode == PATTERN_RED){
		HandlePatternColour(RED);
	} else if(pattern_mode == PATTERN_YELLOW){
		HandlePatternColour(YELLOW);
	} else if(pattern_mode == PATTERN_GREEN){
		HandlePatternColour(GREEN);
	} else if(pattern_mode == PATTERN_RANDOM){
		HandlePatternRandom();
	} else if(pattern_mode == PATTERN_INVERT){
		HandlePatternInvert();
	}
}

void HandlePatternForward(){
	for(int i = 0; i < MAX_LEDS; i++){
		if(leds[i].IsOn()){
			// Turn this LED off.
			leds[i].ToggleOff();
			
			// Turn the next one on
			int next_led = i + 1;
			if(next_led >= MAX_LEDS){
				next_led -= MAX_LEDS;
			}
			leds[next_led].ToggleOn();
			
			// Break loop.
			break;
		}
	}
}

void HandlePatternBackward(){
	for(int i = MAX_LEDS - 1; i >= 0; i--){
		if(leds[i].IsOn()){
			// Turn this LED off.
			leds[i].ToggleOff();
			
			// Turn the next one on.
			int next_led = i - 1;
			if(next_led < 0){
				next_led = MAX_LEDS - 1;
			}
			leds[next_led].ToggleOn();
			
			// Break loop.
			break;
		}
	}
}

void HandlePatternParticles(){
	// Turn off current LEDs.
	leds[partic_1].ToggleOff();
	leds[partic_2].ToggleOff();
	
	// Recalculate particle positions.
	if(partic_1 < MAX_LEDS - 1){
		partic_1++;
	} else {
		partic_1 = 0;
	}
	if(partic_2 > 0){
		partic_2--;
	} else {
		partic_2 = MAX_LEDS - 1;
	}
	
	// Turn on new LEDs.
	leds[partic_1].ToggleOn();
	leds[partic_2].ToggleOn();
}

void HandlePatternColour(int colour){
	// Go trough each LED object.
	for(int i = 0; i < MAX_LEDS; i++){
		if(leds[i].colour == colour){
			// All LED lights of the specified colour are toggled.
			leds[i].Toggle();
		} else {
			// All LED lights of a different colour are turned off.
			leds[i].ToggleOff();
		}
	}
}

void HandlePatternRandom(){
	// Go trough each LED object.
	for(int i = 0; i < MAX_LEDS; i++){
		/* Take a random int from 0 to 10.
		   Note: Extremely low chance of getting 11 due to float value
		   rounding down to nearest integer. */
		int random_int = (int)random(0, 11);
		
		// Essentially we have a 10% chance to light up this LED.
		if(random_int >= 9){
			leds[i].ToggleOn();
		} else {
			leds[i].ToggleOff();
		}
	}
}

void HandlePatternInvert(){
	// Go trough each LED object.
	for(int i = 0; i < MAX_LEDS; i++){
		// Toggle the LED (on/off gets inverted).
		leds[i].Toggle();
	}
}