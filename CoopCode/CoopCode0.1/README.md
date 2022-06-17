# CoopCode v0.1 - The Automated Chicken Coop

First GitHub Commit of Coop Code.

### Overview
Intention of automated chicken coop is to provide an off-grid lighting solution for a chicken house. Lights should go on shortly before dawn and turn off when it's sufficiently light outside.

Requirements:
* Code turns on lights in a chicken coop when natural daylight <14 hours
* Max light burntime is 2 hours
* 
* Minimum dark time of XXX hours
* Off grid capable (no external power)

### Implementation of features for v0
* Solar panel is used to determine day/night
* System is powered by solar panel, charge controller, and battery

### Behavior
* If system started when it's dark - skips next light on cycle and resumes the following morning
* System started when it's light - calculates light-on time at sunset (delay from sunset)
