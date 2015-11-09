
//the pin used to measure
int digitalPin = D0;

//the measurement
int measuredValue = 0;

//a counter to count the milliseconds between measurements
int clockCounter = 0;

void setup(){
  //tell the photon that analogPin is used as an INPUT
  pinMode(digitalPin, INPUT);

  //begin Serial communication
  Serial.begin(9600);

  //make the measurement available in the Cloud
  Particle.variable("measurement",measuredValue);

  //start the clock!
  clockCounter = millis();

}

void loop(){

  //check if digitalPin is high, if so: timestamp.
  if (digitalRead(digitalPin)==HIGH){
    //difference between clockCounter and "now"
    measuredValue = millis() - clockCounter;
    //reset clockCounter
    clockCounter = millis();

    //print over the Serial
    Serial.println(measuredValue);

    //delay a little bit to allow pin to go LOW again
    delay(500);
  }


}
