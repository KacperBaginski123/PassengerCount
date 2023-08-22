/* Bidirectional Visitor Counter using Arduino
   
 */
#include <Wire.h>
#include <rgb_lcd.h>


rgb_lcd lcd; //define pins for LCD Display
#define inSensor 4   //define IR Sensor 1 pins onnnected to D4
#define outSensor 3  //define IR Sensor 2 pins onnnected to D3
#define button 6 //
//Variables
int inStatus;
int outStatus;
int buttonStatus;
 
int in;
int out;
int now;
int countin = 0;
int countout = 0;

bool delayFlag = false; // flag for delay between sensor triggers
unsigned long delayTime = 1000; // delay time in milliseconds
unsigned long previousTime = 0; // initialize previous time to 0
 
 
void setup()
{
  lcd.begin(16, 2); // set up LCD with 16 columns and 2 rows
  lcd.setRGB(255, 255, 255); // set RGB color to white
  //Set Components pin modes
  pinMode(inSensor, INPUT);
  pinMode(outSensor, INPUT);
  pinMode(button, INPUT);
 
  //Print beginning message on LCD Display
  lcd.setCursor(0,0);
  lcd.print("   Welcome!!!   ");
  lcd.setCursor(0,1);
  lcd.print("    To The      ");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Bidirectional  ");
  lcd.setCursor(0,1);
  lcd.print("Visitor Counter");
  delay(3000);
}
 
void loop()
{
  inStatus =  digitalRead(inSensor);  // Read IR Sensor 1 Output
  outStatus = digitalRead(outSensor); // Read IR Sensor 2 Output
  buttonStatus = digitalRead(button);
  // Count the number of entering visitors
  if (inStatus == 0 && !delayFlag && millis() - previousTime > delayTime)
  {
   in = countin++;
   previousTime = millis(); // update previous time
    delayFlag = true; // set delay flag to true
    delay(200);
   
  }
  // Count the number of exiting visitors
  if (outStatus == 0 && !delayFlag && millis() - previousTime > delayTime)
  {
    out = countout++;
    previousTime = millis(); // update previous time
    delayFlag = true; // set delay flag to true
    delay(200);
   
  }
   if (buttonStatus == HIGH)
  {
    out = 0;
    in = 0;
    now = 0;
    countin = 0;
    countout = 0;
    delay(200);
   
  }

    // reset delay flag if delay has passed
  if (millis() - previousTime > delayTime) {
    delayFlag = false; // set delay flag to false
  }
  //calculate currently visitors present inside the place
  now = in - out;
  //Function for when no visitors inside the room
  if (now <= 0)
  {
   
    //Print Data on LCD Display
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" No Passengers  ");
    lcd.setCursor(0,1);
    lcd.print("ON:");
    lcd.setCursor(4,1);
    lcd.print(in);
    lcd.setCursor(8,1);
    lcd.print("OFF:");
    lcd.setCursor(13,1);
    lcd.print(out);
    delay(500);
  }
  // Function for when visitors entering and exiting
  else
  {
   
   
    //Print Data on LCD Display
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("IN:");
    lcd.setCursor(4,0);
    lcd.print(in);
    lcd.setCursor(8,0);
    lcd.print("OUT:");
    lcd.setCursor(13,0);
    lcd.print(out);
    lcd.setCursor(0,1);
    lcd.print("Current =  ");
    lcd.setCursor(9,1);
    lcd.print(now);
    delay(500);
  }
}
