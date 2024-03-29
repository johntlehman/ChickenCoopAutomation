// Include the SparkFun qwiic OLED Library
#include "SparkFun_Qwiic_OLED.h"

QwiicNarrowOLED myOLED; //create an object called myOLED of the QwiicNarrowOLED class

void setup()
{
    Serial.begin(115200);
    Serial.println("Test Serial Comms");

    Wire.begin();

    // Initalize the OLED device and related graphics system
    if (myOLED.begin() == false)
    {
        Serial.println("Device begin failed. Freezing...");
        while (true)
            ;
    }
    Serial.println("Begin success");

    // Do a simple test - fill a rectangle on the screen and then print hello!

    // Fill a rectangle on the screen that has a 4 pixel board
    myOLED.rectangleFill(4, 4, myOLED.getWidth() - 8, myOLED.getHeight() - 8);

    String printString = "tst% Batt"; // message to print to display

    // Center our message on the screen. Get the screen size of the "hello" string,
    // calling the getStringWidth() and getStringHeight() methods on the oled

    // starting x position - screen width minus string width  / 2
    int x0 = (myOLED.getWidth() - myOLED.getStringWidth(printString)) / 2;

    // starting y position - screen height minus string height / 2 
    int y0 = (myOLED.getHeight() - myOLED.getStringHeight(printString)) / 2;

    // Draw the text - color of black (0)
    myOLED.text(x0, y0, printString, 0);

    // There's nothing on the screen yet - Now send the graphics to the device
    myOLED.display();

}   

void loop()
{
    // Leave on for 2 seconds
    myOLED.displayPower(true);
    delay(2000);

    // Turn off for 2 seconds
    myOLED.displayPower(false);
    delay(2000);
}