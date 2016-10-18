#include "LED.h"

LEDLight::LEDLight(){
	// Set voltage state to LOW (turn off).
	this->state = LOW;
}

void LEDLight::Toggle(){
	if(this->state == HIGH){
	// Set voltage state to LOW (turn off).
		this->state = LOW;
	} else {
	// Set voltage state to HIGH (turn on).
		this->state = HIGH;
	}
}

void LEDLight::ToggleOn(){
	// Set voltage state to HIGH (turn on).
	this->state = HIGH;
}

void LEDLight::ToggleOff(){
	// Set voltage state to LOW (turn off).
	this->state = LOW;
}

void LEDLight::SetColour(int colour){
	// Set colour id
	this->colour = colour;
}

bool LEDLight::IsOn(){
	// If voltage is HIGH, return true
	if(this->state == HIGH) return true;
	
	// Otherwise false
	return false;
}