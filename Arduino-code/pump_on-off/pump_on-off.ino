int pumpPin =  5;// the pump mosfet is connected to pin D5 
//long onTime =   600000;  // pump is on for 10 minutes (in ms)
long onTime =   5000;  // pump is on for 5 seconds (in ms)
//long offTime =  1200000; // pump is off for 20 minutes (in ms)
long offTime =  10000; // pump is off for 10 seconds (in ms)

class Switcher
{
    int switchPin;
    long onTime;
    long offTime;

    int switchState;
    unsigned long previousMillis;

    public:
    Switcher(int pin, long on, long off)
    {
      switchPin = pin;
      pinMode(switchPin, OUTPUT);

      onTime = on;
      offTime = off;

      switchState = LOW;
      previousMillis = 0;
    }

    void Update()
    {
      unsigned long currentMillis = millis();

      if((switchState == HIGH) &&  (previousMillis >= onTime))
      {
        switchState = LOW;
        previousMillis = currentMillis;
        digitalWrite(switchPin, switchState);
      }
      else if ((switchState == LOW) && (currentMillis - previousMillis >= offTime))
      {
        switchState = HIGH;
        previousMillis = currentMillis;
        digitalWrite(switchPin, switchState);
      }
    }
};

Switcher pump(pumpPin,onTime,offTime);

void setup() { 
}

void loop() {
  pump.Update();
}
