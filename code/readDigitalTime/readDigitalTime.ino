/* 
script do to time measurements (number of pulses within an interval. 
- every second, a measurement (as integer) is written over the Serial line
- every 5 seconds, a measurement (as integer) is published to the Cloud
- the function "readPulses" is call-able from the Cloud. A measurement (as integer!)
  is returned. 
*/

//the interval used to measure, in milliseconds
int measureTime = 1000;

//the interval used to measure, in milliseconds
int measureTimeOnline = 5000;
//the name of the event.
String eventName = "measurement/JuniorTUDelft/studentName";

//the pin to use for measuring.
String digitalPin = "D0";

//some constants and constructs
int measuredPulsesSerial = 0;
int measuredPulsesOnline = 0;
int measuredPulsesSerialPrevious = 0;

Timer measureTimer(measureTime, readAndSerial);
Timer measureTimerOnline(measureTimeOnline, readAndPublish);

void setup(){
  //start Serial communication
  Serial.begin(9600);

  //set analogPin to INPUT
  int pin = digitalPin.toInt();
  pinMode(pin, INPUT);

  //attach an interupt for handling counting the pulses
  attachInterrupt(pin, pulse, RISING);

  //start timer that calls measurement en sends results over Serial
  measureTimer.start();
  measureTimerOnline.start();
  

  //make measuredPulsesSerialPrevious available online
  Particle.variable("measurement",measuredPulsesSerialPrevious);

  //make readAnalogValue available online, returns measurement as integer
  Particle.function("readPulsesPerSecond",readPulses);
}

void loop(){}

void readAndSerial(){
  Serial.println(measuredPulsesSerial);
  measuredPulsesSerialPrevious=measuredPulsesSerial;
  measuredPulsesSerial=0;
}

void readAndPublish(){
  Particle.publish(eventName, (String) measuredPulsesOnline);
  measuredPulsesOnline=0;
}

//readPulses only returns the nr of pulses from the previous second.
int readPulses(String Command){
  return measuredPulsesSerialPrevious;
}

void pulse(){
    measuredPulsesSerial++;
    measuredPulsesOnline++;
}
