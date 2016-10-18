# Arduino LED Train

This is my first Arduino project using C++. The code programs the board to create various patterns using 10 LED (or whatever desired amount) lights. Here's a video demonstrating it: https://www.youtube.com/watch?v=8az_PUpH-Qc
Big thanks to Andrew and his genius son who supplied me with the components to play around with :)

The physical components used:
  - Arduino UNO board
  - 10 LED lights
  - 11 resistors (x10 220 ohm, x1 10 ohm)
  - 1 Button
  - 1 Analog sensor
  - 17 wires
  
If you want to attempt to rebuild it yourself, here are the pins used:
  [Port]       [Component]    [Mode]
  DIGITAL 3    button         INPUT
  DIGITAL 4    LED #1         OUTPUT
  DIGITAL 5    LED #2         OUTPUT
  DIGITAL 6    LED #3         OUTPUT
  DIGITAL 7    LED #4         OUTPUT
  DIGITAL 8    LED #5         OUTPUT
  DIGITAL 9    LED #6         OUTPUT
  DIGITAL 10   LED #7         OUTPUT
  DIGITAL 11   LED #8         OUTPUT
  DIGITAL 12   LED #9         OUTPUT
  DIGITAL 13   LED #10        OUTPUT
  ANALOG 0     Sensor         INPUT
