#include <TimerFreeTone.h>

#define TONE_PIN 6 // Pin you have speaker/piezo connected to (be sure to include a 100 ohm resistor).

// Melody (liberated from the toneMelody Arduino example sketch by Tom Igoe).
int melody[] = {1000};
int duration[] = { 500};


#include <Battery.h>

Battery battery(11000, 13500, A0);
//11000 is the level which the 12v bat is concidered low
//13500 is the level which the bat is concidered full 100%

int battMin = 0;
int battMax = 0;
int led = 13;



const int SpwmArry[] = {100, 250, 350, 450, 500, 650, 750, 850, 1000, 1250, 1250, 1000, 850, 750, 650, 500, 450, 350, 250, 100};
const int SpwmArryValues = 20; //Put length of an Array depends on SpwmArray numb
// Declare the output pins and choose PWM pins only
const int sPWMpin1 = 10;
const int sPWMpin2 = 9;
// enabling bool status of Spwm pins
bool sPWMpin1Status = true;
bool sPWMpin2Status = true;
void setup()
{
  Serial.begin(9600);
  while (!Serial);
  battery.begin(5000, 2.780);
  pinMode (led, OUTPUT); 
  pinMode(sPWMpin1, OUTPUT);
  pinMode(sPWMpin2, OUTPUT);
  digitalWrite(led, LOW);
}
void loop()
{
 inverting();
// batt_monitor();
}

void batt_monitor(){
 
  battMin = battery.voltage();
  battMax = battery.voltage();
  //Serial.print("Battery voltage is ");
  //Serial.println(battery.voltage());
  /*Serial.print(" (");
  Serial.print(battery.level());
  Serial.println("%)");*/
  if (battMin <= 12300){
     digitalWrite(led, HIGH);

    for (int thisNote = 0; thisNote < 8; thisNote++) { // Loop through the notes in the array.
    TimerFreeTone(TONE_PIN, melody[thisNote], duration[thisNote]); // Play melody[thisNote] for duration[thisNote].
    delay(50); // Short delay between notes.
  } 
  }
  else{
    digitalWrite(led, LOW);
  }
  
}
void inverting(){

   // Loop for Spwm pin 1
  for (int i(0); i != SpwmArryValues; i++)
  {
    if (sPWMpin1Status)
    {
      digitalWrite(sPWMpin1, HIGH);
      delayMicroseconds(SpwmArry[i]);
      sPWMpin1Status = false;
    }
    else
    {
      digitalWrite(sPWMpin1, LOW);
      delayMicroseconds(SpwmArry[i]);
      sPWMpin1Status = true;
    }
  }

  // Loop for Spwm pin 2
  for (int i(0); i != SpwmArryValues; i++)
  {
    if (sPWMpin2Status)
    {
      digitalWrite(sPWMpin2, HIGH);
      delayMicroseconds(SpwmArry[i]);
      sPWMpin2Status = false;
    }
    else
    {
      digitalWrite(sPWMpin2, LOW);
      delayMicroseconds(SpwmArry[i]);
      sPWMpin2Status = true;
    }
  }
}
