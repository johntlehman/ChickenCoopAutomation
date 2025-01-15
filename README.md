# CoopCode - The Automated Chicken Coop

### Overview
Intention of automated chicken coop is to provide an off-grid lighting solution for a chicken house. Lights should go on shortly before dawn and turn off when it's sufficiently light outside.

Requirements:
* Code turns on lights in a chicken coop when natural daylight <14 hours
* 
* Off grid capable (no external power)

### Implementation of features for v0
* 

### Assumes the Following Hardware Implementation
* LED Stick connected via I2C
* RTC connected via I2C
* Photosensitive resistor is used to determine day/night, voltage measured via analog pin
* System is powered by external solar panel, charge controller, and battery
* System measures external battery voltage via a voltage divider, voltage measured via analog pin

### Behavior
* System powered up during 'day' time
    * Sunrise time stored as whenever system is turned on
    * Calculates alarm time delay from sunrise (default 10 hours)
    * Calculates alarm time at sunset (delay from sunset, default 22 hours)
    * Stores alarm as whichever is greater
    * Turns on lights at alarm time
* System powered up during 'night' time
    * Sunrise time stored when sunrise detected
* System started when it's light -