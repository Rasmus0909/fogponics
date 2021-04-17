int pumpPin =  5;// the pump mosfet is connected to pin D5 
long onTime =   600000;  // pump is on for 10 minutes (in ms)
long offTime =  1200000; // pump is off for 20 minutes (in ms)

//long onTime =   5000;  // pump is on for 5 seconds (in ms)
//long offTime =  10000; // pump is off for 10 seconds (in ms)

class Switcher // General purpose class for switching digital pins on/off
{
    int switchPin; // the pin to be switched
    long onTime; // how long the pin has to be on for
    long offTime; // how long the pin has to be off for

    int switchState; // what state the pin is in, on/off
    unsigned long previousMillis; // for time keeping

    public:
    Switcher(int pin, long on, long off, boolean startup) // the constructor
    {
      switchPin = pin; // assign the pin
      pinMode(switchPin, OUTPUT); // set pin as output

      onTime = on; // define the on-time in [ms]
      offTime = off; // define the off-time in [ms]

      switchState = startup; // the state the pin starts out in
      digitalWrite(switchPin,switchState);
      previousMillis = 0; //
    }

    void Update()
    {
      unsigned long currentMillis = millis();

      if((switchState == HIGH) &&  (currentMillis - previousMillis >= onTime)) // checking if it's time to turn off the pin
      {
        switchState = LOW;
        previousMillis = currentMillis;
        digitalWrite(switchPin, switchState);
      }
      else if ((switchState == LOW) && (currentMillis - previousMillis >= offTime)) // checking if it's time to turn off the pin
      {
        switchState = HIGH;
        previousMillis = currentMillis;
        digitalWrite(switchPin, switchState);
      }
    }
};

Switcher pump(pumpPin,onTime,offTime,HIGH);

void setup() { 
  delay(100); // allow the system to power up properly before code is started
}

void loop() {
  pump.Update();
}
