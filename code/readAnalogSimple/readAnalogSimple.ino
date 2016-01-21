/* 
script do to analog measurements. 
- every second, a measurement (as floating point) is written over the Serial line
- every 5 seconds, a measurement (as floating point) is published to the Cloud
- the function "readAnalog" is call-able from the Cloud. A measurement (as integer!)
  is returned. 
*/

//the interval used to measure, in milliseconds
int measureTime = 1000;

//the interval used to measure, in milliseconds
int measureTimeOnline = 5000;
//the name of the event.
String eventName = "measurement/JuniorTUDelft/studentName";

//the pin to use for measuring.
String analogPin = "A0";

//some constants and constructs
int measuredBitValue = 0;
float measuredValue = 0.0;

Timer measureTimer(measureTime, readAndSerial);
Timer measureTimerOnline(measureTimeOnline, readAndPublish);

void setup(){
  //start Serial communication
  Serial.begin(9600);

  //set analogPin to INPUT
  int pin = analogPin.toInt();
  pinMode(pin, INPUT);

  //start timer that calls measurement en sends results over Serial
  measureTimer.start();

  //make measuredValue available online
  Particle.variable("measurement",measuredValue);

  //make readAnalogValue available online, returns measurement as integer
  Particle.function("readAnalog",readAnalogValue);
}

void loop(){}

void readAndSerial(){
  readAnalogValue(analogPin);
  Serial.println(measuredValue);
}

void readAndPublish(){
  readAnalogValue(analogPin);
  Particle.publish(eventName, (String) measuredValue);
}

//readAnalog is done in two steps to allow calling readAnalogValue from the Cloud
int readAnalogValue(String Command){
  int pin = Command.toInt();
  if (getPinMode(pin)==INPUT){
    measuredBitValue = analogRead(pin);
    measuredValue = convertBit2Measured(measuredBitValue);
    return measuredBitValue;
  } else {
    measuredBitValue = -1;
    measuredValue = -1.0;
    return -1;
  }
}

float convertBit2Measured (int bitValue){
  //first convert to Voltage
  float voltageValue = (float) bitValue * 3.3 / 4096.0;

  //then convert to measured value using calibration. Change the line below as
  //needed.
  float value = voltageValue;

  return value;
}
